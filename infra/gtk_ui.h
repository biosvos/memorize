//
// Created by biosvos on 10/11/22.
//

#ifndef MEMORIZE_GTK_UI_H
#define MEMORIZE_GTK_UI_H

#include <memory>
#include "../usecase/usecase.h"

class GtkUi {
public:
    explicit GtkUi(std::shared_ptr<IUsecase> usecase);

    void Run();

private:
    std::shared_ptr<IUsecase> usecase_;
};


#endif //MEMORIZE_GTK_UI_H
