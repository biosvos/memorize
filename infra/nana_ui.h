//
// Created by biosvos on 11/18/22.
//

#ifndef MEMORIZE_NANA_UI_H
#define MEMORIZE_NANA_UI_H

#include <memory>
#include "../usecase/usecase.h"

class NanaUi {
public:
    explicit NanaUi(std::shared_ptr<IUsecase> usecase);

    void Run();

private:
    std::shared_ptr<IUsecase> usecase_;
};


#endif //MEMORIZE_NANA_UI_H
