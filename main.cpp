#include "view/ViewConsole.hpp"
#include <fstream>


int main() {
    try {
        Loader loader;
        auto presenter = loader.create_default_presenter();

        ViewConsole view(std::move(presenter));
        view.run(0);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}