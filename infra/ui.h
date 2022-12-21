//
// Created by biosvos on 12/20/22.
//

#ifndef MEMORIZE_UI_H
#define MEMORIZE_UI_H

#include <memory>
#include "../usecase/usecase.h"

class Ui {
public:
    explicit Ui(std::shared_ptr<IUsecase> usecase);

    void Run();

private:
    std::shared_ptr<IUsecase> usecase_;
};


#endif //MEMORIZE_UI_H
