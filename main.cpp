#include <iostream>
#include <vector>
#include <memory>

struct Component{
    virtual void getLayout(){
        std::cout << "Component::layout\n";
    }
};
struct Container:Component{
    std::vector<std::unique_ptr<Component>> components;
    Container() = default;
    Container(const Container &) = delete;
    void getLayout() override{
        std::cout << "Container::layout\n";
    }
    void layout(){}
};
struct Label:Component
{
    Label() = default;
    Label(std::string text):text(text){}
    void getLayout() override{
        std::cout << "Label::layout\n";
    }
    std::string text;
};

void inspect(Container& c){

    for(auto& up:c.components){
        auto& component = *up.get();
        try{
            auto& label = dynamic_cast<Label&>(component);
            std::cout << label.text << "\n";
        }catch (std::bad_cast bc){
            std::cout << bc.what() << "\n";
        }
/**        if(auto ptr = dynamic_cast<Label*>(component)){
            std::cout << "Text of Label: " << ptr->text << "\n";
        }else{
            std::cout << "Ingen label\n";
        }*/
    }
}

int main() {
    Container c;

    c.components.push_back(std::make_unique<Label>("Hej"));
    c.components.push_back(std::make_unique<Component>());

    try{
        inspect(c);
    }catch(...){
        std::cout << "Ajaj\n";
    }

}
