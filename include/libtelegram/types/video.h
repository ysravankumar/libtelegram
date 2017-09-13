#ifndef TELEGRAM_TYPES_VIDEO_H_INCLUDED
#define TELEGRAM_TYPES_VIDEO_H_INCLUDED

#include "helpers/optional.h"

namespace telegram::types {

struct video {
  /// See https://core.telegram.org/bots/api#video
  std::string file_id;                                                          // Unique identifier for this file
  std::optional<int_fast32_t> width;                                            // Optional. Video width as defined by sender
  std::optional<int_fast32_t> height;                                           // Optional. Video height as defined by sender
  std::optional<int_fast32_t> duration;                                         // Optional. Duration of the video in seconds as defined by sender
  std::optional<photosize> thumb;                                               // Optional. Video thumbnail
  std::optional<std::string> mime_type;                                         // Optional. MIME type of the file as defined by sender
  std::optional<int_fast32_t> file_size;                                        // Optional. File size (in bytes)

  static video const from_json(nlohmann::json const &tree);
  static video const from_json(nlohmann::json const &tree, std::string const &path);
};

video const video::from_json(nlohmann::json const &tree) {
  /// Factory to generate a struct of this type from the correct property tree
  /// If any non-optional elements are missing from the tree, throws std::domain_error
  return video{tree.at("file_id"),
               helpers::make_optional_from_json<int_fast32_t>(tree, "width"),
               helpers::make_optional_from_json<int_fast32_t>(tree, "height"),
               helpers::make_optional_from_json<int_fast32_t>(tree, "duration"),
               helpers::make_optional_from_json<photosize>(tree, "thumb"),
               helpers::make_optional_from_json<std::string>(tree, "mime_type"),
               helpers::make_optional_from_json<int_fast32_t>(tree, "file_size")};
}
video const video::from_json(nlohmann::json const &tree, std::string const &path) {
  /// Helper to generate a struct of this type from a path within a tree
  /// If there is no such child, throws std::domain_error
  return from_json(tree.at(path));
}

}

#endif // TELEGRAM_TYPES_VIDEO_H_INCLUDED
