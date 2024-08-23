#include "nspi_app.h"

// external
#include <curl/curl.h>

#include <nlohmann/json.hpp>

// std
#include <iostream>
#include <sstream>

nspi::App::App() : quit(false) { this->init(); }

nspi::App::~App() { this->clean(); }

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
  size_t totalSize = size * nmemb;
  userp->append((char*)contents, totalSize);
  return totalSize;
}

// Helper function to safely copy strings into fixed-size char arrays
static void copyStringToCharArray(const std::string& source, char* destination, size_t maxSize) {
  strncpy(destination, source.c_str(), maxSize - 1);
  destination[maxSize - 1] = '\0';  // Ensure null termination
}

std::string nspi::App::retrieveRawDataFromEndpoint() const {
  CURL* curl;
  CURLcode res;
  std::string responseBody;

  const std::string apiEndpoint =
      "https://raw.githubusercontent.com/ghost-land/NX-DB/main/fulldb.json";

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, apiEndpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBody);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      std::stringstream ss;
      ss << "curl_easy_perform() failed: " << curl_easy_strerror(res);
      throw new std::runtime_error(ss.str());
    }

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return responseBody;
}

std::vector<nspi::Title> nspi::App::retrieveTitlesFromRawData(const std::string& rawData) const {
  std::vector<nspi::Title> titles;

  nlohmann::json jsonData;
  try {
    jsonData = nlohmann::json::parse(rawData);

    if (jsonData.contains("titledb") && jsonData["titledb"].is_object()) {
      nlohmann::json titledb = jsonData["titledb"];
      int count = 0;

      for (nlohmann::json::iterator it = titledb.begin(); it != titledb.end(); ++it) {
        if (count >= 20000) break;  // Limit amount of entries available

        const nlohmann::json& value = it.value();
        Title title;

        // Initialize the struct with default values
        std::memset(&title, 0, sizeof(Title));

        // Fill the struct fields
        if (value.contains("id") && value["id"].is_string()) {
          copyStringToCharArray(value["id"].get<std::string>(), title.id, sizeof(title.id));
        }

        if (value.contains("region") && value["region"].is_string()) {
          copyStringToCharArray(
              value["region"].get<std::string>(),
              title.region,
              sizeof(title.region));
        }

        if (value.contains("name") && value["name"].is_string()) {
          copyStringToCharArray(value["name"].get<std::string>(), title.name, sizeof(title.name));
        }

        if (value.contains("size") && value["size"].is_number_integer()) {
          title.size =
              static_cast<uint16_t>(value["size"].get<uint64_t>());  // Ensure size fits in uint16_t
        }

        titles.push_back(title);

        ++count;
      }
    } else {
      std::cerr << "'titledb' not found or is not an object\n";
    }
  } catch (const nlohmann::json::parse_error& e) {
    std::cerr << "Parse error: " << e.what() << '\n';
  }

  return titles;
}

void nspi::App::init() {
  socketInitializeDefault();

  std::string rawData = this->retrieveRawDataFromEndpoint();
  std::vector<nspi::Title> titles = this->retrieveTitlesFromRawData(rawData);

  this->menu.addEntries(titles);
}

void nspi::App::clean() { socketExit(); }

bool nspi::App::shouldClose() const { return this->quit || !appletMainLoop(); }

void nspi::App::mainLoop() {
  while (!this->shouldClose()) {
    this->handleInput();
    // some logic ???
    this->draw();
  }
}

void nspi::App::handleInput() {
  this->pad.update();
  u64 kDown = this->pad.getButtonsDown();
  if (kDown & HidNpadButton_Plus) {
    this->quit = true;
  }

  // delegate input to current menu after critical input checks
  this->menu.handleInput();
}

void nspi::App::draw() {
  this->menu.draw();
  this->console.update();
}

void nspi::App::run() { this->mainLoop(); }