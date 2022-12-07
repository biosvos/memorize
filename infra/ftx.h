//
// Created by biosvos on 12/5/22.
//

#ifndef MEMORIZE_FTX_H
#define MEMORIZE_FTX_H

#include <memory>
#include "../usecase/usecase.h"

class Ftx {
public:
    explicit Ftx(std::shared_ptr<IUsecase> usecase);

    void Run();

private:
    void MainEntry();

    void Add();

    std::shared_ptr<IUsecase> usecase_;

    void Train1(IUsecase::Card &card);

    void Train2(IUsecase::Card &card);

    void List();
};


#endif //MEMORIZE_FTX_H
