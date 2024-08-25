#include "nspi_title_selector_menu.h"

#include "nspi_title_menu.h"

// external
#include <curl/curl.h>

#include <nlohmann/json.hpp>

// std
#include <iomanip>
#include <iostream>

void nspi::TitleSelectorMenu::printFooter() const {
  uint16_t printableFocusIndex = 0;
  if (this->dummyData.size() != 0) {
    printableFocusIndex = focusIndex + 1;
  }

  std::stringstream nav_info;
  nav_info << "(" << (int)printableFocusIndex << "/" << this->dummyData.size() << ")";

  uint8_t remaining_width = CONSOLE_WIDTH - nav_info.str().length();

  std::cout << "-------------------------------------------------------------------------------\n";
  std::cout << nav_info.str() << std::setw(remaining_width) << std::right
            << "[-] Load [+] Exit [X] De/Select [Y] Info [B] Back \e[9m[A] Install\e[0m\n";
}

void nspi::TitleSelectorMenu::printContent() const {
  size_t printedItems = 0;
  for (size_t i = focusOffset; i < dummyData.size(); i++) {
    if (printedItems >= VISIBLE_ITEMS) break;

    if (i == this->focusIndex) {
      std::cout << "\033[1;41m";  // Highlight focused item
    } else if (this->marked.find(i) != this->marked.end()) {
      std::cout << "\033[1;43m";  // Highlight marked item
    }

    std::string name = dummyData[i].name;
    if (name.length() > 40) {
      name = name.substr(0, 37) + "...";
    }

    // clang-format off
    std::cout << std::setw(17) << std::left << dummyData[i].id
              << std::setw(3) << std::left << dummyData[i].region
              << std::setw(40) << std::left << name
              << std::setw(16) << std::right << dummyData[i].size << " B"
              << "\033[0m" << std::endl;
    // clang-format on

    printedItems++;
  }

  // Padding for empty rows
  while (printedItems < VISIBLE_ITEMS) {
    std::cout << std::endl;
    printedItems++;
  }
}

nspi::TitleSelectorMenu::TitleSelectorMenu(MenuManager& menuManager, Pad& pad)
    : focusIndex(0), focusOffset(0), menuManager(menuManager), pad(pad) {}

void nspi::TitleSelectorMenu::handleInput() {
  u64 kDown = this->pad.getButtonsDown();
  HidAnalogStickState left_stick_state = this->pad.getStickPos(0);
  // HidAnalogStickState right_stick_state = this->pad.getStickPos(1);

  if (kDown & HidNpadButton_Up || left_stick_state.y > 30000) {
    this->focusPrevious();
  }

  if (kDown & HidNpadButton_Down || left_stick_state.y < -30000) {
    this->focusNext();
  }

  if (kDown & HidNpadButton_Left || left_stick_state.x < -30000) {
    this->focusPrevious(5);
  }

  if (kDown & HidNpadButton_Right || left_stick_state.x > 30000) {
    this->focusNext(5);
  }

  if (kDown & HidNpadButton_X) {
    if (this->marked.find(focusIndex) == this->marked.end()) {
      this->marked.insert(focusIndex);
    } else {
      this->marked.erase(focusIndex);
    }
  }

  static bool contentLoaded = false;
  if (kDown & HidNpadButton_Minus && !contentLoaded) {
    std::vector<nspi::Title> titles =
        this->fetchTitles("https://raw.githubusercontent.com/blawar/titledb/master/ES.es.json");

    this->dummyData = titles;

    contentLoaded = true;
  }

  if (kDown & HidNpadButton_Y) {
    if (!dummyData.empty()) {
      this->menuManager.next(new TitleMenu(menuManager, pad, dummyData[focusIndex]));
    }
  }

  // Adjust focusOffset if necessary
  if (focusIndex < focusOffset) {
    focusOffset = focusIndex;
  } else if (focusIndex >= focusOffset + VISIBLE_ITEMS) {
    focusOffset = focusIndex - VISIBLE_ITEMS + 1;
  }
}

void nspi::TitleSelectorMenu::focusPrevious(uint16_t steps) {
  if (this->focusIndex < steps) {
    this->focusIndex = 0;
  }

  if (this->focusIndex != 0) {
    this->focusIndex -= steps;
  }
}

void nspi::TitleSelectorMenu::focusNext(uint16_t steps) {
  if (this->dummyData.size() == 0) {
    this->focusIndex = 0;
    return;
  }

  if (this->focusIndex + steps > this->dummyData.size()) {
    this->focusIndex = this->dummyData.size() - 1;
  }

  if (this->focusIndex < this->dummyData.size() - 1) {
    this->focusIndex += steps;
  }
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
  size_t totalSize = size * nmemb;
  userp->append((char*)contents, totalSize);
  return totalSize;
}

static void copyStringToCharArray(const std::string& source, char* destination, size_t size) {
  strncpy(destination, source.c_str(), size - 1);
  destination[size - 1] = '\0';  // Ensure null termination
}

static void populateTitleField(
    const nlohmann::json& value, const std::string& field, char* destination, size_t size) {
  if (value.contains(field) && value[field].is_string()) {
    copyStringToCharArray(value[field].get<std::string>(), destination, size);
  }
}

std::string nspi::TitleSelectorMenu::retrieveRawDataFromEndpoint(
    const std::string& endpoint) const {
  CURL* curl;
  CURLcode res;
  std::string responseBody = "";

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBody);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      std::stringstream ss;
      ss << "curl_easy_perform() failed: " << curl_easy_strerror(res);

      std::cerr << ss.str() << std::endl;
    }

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return responseBody;
}

std::vector<nspi::Title> nspi::TitleSelectorMenu::retrieveTitlesFromRawData(
    const std::string& rawData) const {
  std::vector<Title> titles;

  nlohmann::json jsonData = nlohmann::json::parse(rawData, nullptr, false);
  if (jsonData.is_discarded()) {
    std::cerr << "Failed to parse raw data into JSON.\n";
    return titles;
  }

  const nlohmann::json& titledb = jsonData;
  int count = 0;

  for (auto it = titledb.begin(); it != titledb.end(); ++it) {
    if (count >= 60000) break;  // Limit amount of entries available

    const nlohmann::json& value = it.value();
    const std::string key = it.key();

    Title title;
    std::memset(&title, 0, sizeof(Title));

    if (value.contains("releaseDate") && value["releaseDate"].is_number_integer()) {
      title.releaseDate = value["releaseDate"].get<uint32_t>();
    }

    if (value.contains("size") && value["size"].is_number_integer()) {
      title.size = value["size"].get<uint32_t>();
    }

    copyStringToCharArray(key, title.id, sizeof(title.id));
    populateTitleField(value, "region", title.region, sizeof(title.region));
    populateTitleField(value, "publisher", title.publisher, sizeof(title.publisher));
    populateTitleField(value, "name", title.name, sizeof(title.name));
    populateTitleField(value, "version", title.version, sizeof(title.version));
    populateTitleField(value, "description", title.description, sizeof(title.description));

    titles.push_back(title);
    ++count;
  }

  return titles;
}

std::vector<nspi::Title> nspi::TitleSelectorMenu::fetchTitles(const std::string& endpoint) const {
  std::string rawData = this->retrieveRawDataFromEndpoint(endpoint);
  return this->retrieveTitlesFromRawData(rawData);
}
