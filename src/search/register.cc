/*
  This file is part of Leela Chess Zero.
  Copyright (C) 2018-2020 The LCZero Authors

  Leela Chess is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Leela Chess is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Leela Chess.  If not, see <http://www.gnu.org/licenses/>.

  Additional permission under GNU GPL version 3 section 7

  If you modify this Program, or any covered work, by linking or
  combining it with NVIDIA Corporation's libraries from the NVIDIA CUDA
  Toolkit and the NVIDIA CUDA Deep Neural Network library (or a
  modified version of those libraries), containing parts covered by the
  terms of the respective license agreement, the licensors of this
  Program grant you additional permission to convey the resulting work.
*/

#include "search/register.h"

#include <algorithm>

namespace lczero {

SearchManager* SearchManager::Get() {
  static SearchManager factory;
  return &factory;
}

void SearchManager::AddSearchFactory(std::unique_ptr<SearchFactory> algorithm) {
  algorithms_.push_back(std::move(algorithm));
}

std::vector<std::string_view> SearchManager::GetSearchNames() const {
  std::vector<std::string_view> res;
  res.reserve(algorithms_.size());
  std::transform(algorithms_.begin(), algorithms_.end(),
                 std::back_inserter(res),
                 [](const auto& alg) { return alg->GetName(); });
  return res;
}

SearchFactory* SearchManager::GetFactoryByName(std::string_view name) const {
  auto it =
      std::find_if(algorithms_.begin(), algorithms_.end(),
                   [name](const auto& alg) { return alg->GetName() == name; });
  return it == algorithms_.end() ? nullptr : it->get();
}

}  // namespace lczero