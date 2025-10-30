#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    window->setWindowTitle("Enter Your Age");

    QSpinBox *spinBox = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);
    spinBox->setRange(0, 130);
    slider->setRange(0, 130);

    // QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    // QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

    // Qt 5 及以后的新写法
    QObject::connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);
    QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    spinBox->setValue(35);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    window->setLayout(layout);

    window->show();

    return app.exec();
}
