#include "soundadjtest.h"
#include <QPushButton>
#include <QSlider>
#include <QSignalSpy>
#include <QApplication>

void soundAdjTest::testVolumeButton()
{
    QWidget widget;
    QPushButton volumeButton("Volume", &widget);
    QVERIFY(volumeButton.isVisible());

    // Create a signal spy to monitor the signal emitted when the button is clicked
    QSignalSpy spy(&volumeButton, &QPushButton::clicked);

    // Simulate a button click
    QTest::mouseClick(&volumeButton, Qt::LeftButton);

    // Verify the volume button
    if (spy.count() == 1) {
        qDebug() << "Volume button test: Valid";
    } else {
        qDebug() << "Volume button test: Invalid";
    }
}

void soundAdjTest::testSlider()
{
    QWidget widget;

    // Create a slider to simulate volume control
    QSlider volumeSlider(Qt::Horizontal, &widget);
    volumeSlider.setRange(0, 100);  // Set volume range (0 to 100)
    volumeSlider.setValue(50);  // Set initial value to 50

    // Verify the initial value is set correctly
    QCOMPARE(volumeSlider.value(), 50);

    // Create a signal spy to monitor the valueChanged signal from the slider
    QSignalSpy spy(&volumeSlider, &QSlider::valueChanged);

    // Simulate changing the slider value to 75
    QTest::keyClicks(&volumeSlider, "75");

    // Verify that the slider value has changed and the signal was emitted
    QCOMPARE(volumeSlider.value(), 75);

    // Verify that the slider value has changed
    if (volumeSlider.value() == 75 && spy.count() == 1) {
        qDebug() << "Slider test: Valid";
    } else {
        qDebug() << "Slider test: Invalid";
    }
}

