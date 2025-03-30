/**
 * @file soundadjtest.h
 * @author Julie Vo
 * @date 30 March 2025
 * @brief File containing sound adjustment test header.
 *
 */

#ifndef SOUNDADJTEST_H
#define SOUNDADJTEST_H

#include <QObject>
#include "soundadjtest.h"
#include <QTest>

class soundAdjTest : public QObject {
    Q_OBJECT

private slots:
    // Test accessing sound setting.
    void testVolumeButton();

    // Test adjusting music voume.
    void testSlider();

};

#endif // SOUNDADJTEST_H
