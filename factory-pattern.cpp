#include <iostream>

class IButton {
public:
    virtual void render(int a, int b) = 0;
    virtual void onClick(int f) = 0;
};

class Dialog {
public:
    Dialog() = default;
    virtual IButton* createButton() = 0;

    void render()
    {
        IButton* okButton = createButton();
        okButton->onClick(0);
        okButton->render(0, 1);
    }
};

class WindowsButton : public IButton {
    void render(int a, int b) override
    {
        std::cout << "Rendering a WindowsButton\n";
    }

    void onClick(int f) override
    {
        std::cout << "WindowsButton clicked\n";
    }
};


class HTMLButton : public IButton {
    void render(int a, int b) override
    {
        std::cout << "Rendering a HTMLButton\n";
    }

    void onClick(int f) override
    {
        std::cout << "HTMLButton clicked\n";
    }
};

class WindowsDialog : public Dialog {
public:
    WindowsDialog() = default;
    IButton* createButton() override
    {
        return new WindowsButton();
    }
};


class WebDialog : public Dialog {
public:
    WebDialog() = default;
    IButton* createButton() override
    {
        return new HTMLButton();
    }
};


class Application {
private:
    Dialog* dialog;
public:
    void initialize()
    {
        std::string os = "Web";

        if (os == "Windows") {
            dialog = new WindowsDialog();
        }
        else if (os == "Web") {
            dialog = new WebDialog();
        }
        else {
            std::cerr << "Error! Unkown operating system.\n";
        }
    }

    void start()
    {
        this->initialize();
        dialog->render();
    }
};


int main(int argc, char const *argv[])
{
    Application app;
    app.initialize();
    app.start();
    return 0;
}

