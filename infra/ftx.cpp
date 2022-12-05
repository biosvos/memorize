//
// Created by biosvos on 12/5/22.
//

#include "ftx.h"

#include <utility>

Ftx::Ftx(std::shared_ptr<IUsecase> usecase) : usecase_(std::move(usecase)) {}

void Ftx::Run() {

}
