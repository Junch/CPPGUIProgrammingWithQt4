#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPushButton *button = new QPushButton("Quit");
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
    // 现代Qt 5写法 - 使用新的信号槽语法
    QObject::connect(button, &QPushButton::clicked, &app, &QApplication::quit);
    button->show(); 
    return app.exec();
}
