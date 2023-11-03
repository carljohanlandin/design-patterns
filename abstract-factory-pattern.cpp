#include <iostream>

class IGUIFactory {
public:
    virtual IButton createButton() = 0;
    virtual ICheckbox createCheckbox() = 0;
}

class WinFactory : public IGUIFactory {
    IButton* createButton() override
    {
        return new WinButton();
    }

    ICheckbox* createCheckbox() override
    {
        return new WinCheckbox();
    }
}

class MacFactory : public IGUIFactory {
    IButton* createButton() override
    {
        return new MacButton();
    }

    ICheckbox* createCheckbox() override
    {
        return new MacCheckbox();
    }
}

class IButton {
public:
    virtual void paint() = 0;
}

class WinButton : public IButton {
    void paint() override
    {
        cout << "Rendering a Windows Button\n";
    }
}

class MacButton : public IButton {
    void paint() override
    {
        cout << "Rendering a Mac Button\n";
    }
}

class ICheckbox {
public:
    virtual void paint() = 0;
}

class WinCheckbox : public ICheckbox {
    void paint() override
    {
        std::cout
    }
}
