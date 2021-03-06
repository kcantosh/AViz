#include "../fileFunctions.h"

#include <QtTest/QtTest>
#include <QString>

#include "../exceptions.h"

#if QT_VERSION < 0x050300
// Our test system uses Qt5.2 but QVERIFY_EXCEPTION_THROWN first appears in Qt5.3
    #include "verify_exception.h"
#endif

class TestFileFunctions: public QObject
{
    Q_OBJECT
private slots:
    void parseParticleLineSimple() {
      auto p = parseParticleLine("X0 1.030e+04 1.040e+03 1.030e+04");

      QCOMPARE(p.x, 1.030e+04);
      QCOMPARE(p.y, 1.040e+03);
      QCOMPARE(p.z, 1.030e+04);
    }

    void parseParticleLineSimpleTrailingSpace() {
      auto p = parseParticleLine("X0 1.030e+04 1.040e+03 1.030e+04  ");

      QCOMPARE(p.x, 1.030e+04);
      QCOMPARE(p.y, 1.040e+03);
      QCOMPARE(p.z, 1.030e+04);
    }

    void parseParticleLineWithParameters() {
        auto p = parseParticleLine("X0 1.030e+04 1.040e+03 1.030e+04 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0");
        QCOMPARE(p.x, 1.030e+04);
        QCOMPARE(p.y, 1.040e+03);
        QCOMPARE(p.z, 1.030e+04);
        QCOMPARE(p.type.type, "X0");
        QCOMPARE(p.prop1, 1.0);
        QCOMPARE(p.prop2, 2.0);
        QCOMPARE(p.prop3, 3.0);
        QCOMPARE(p.prop4, 4.0);
        QCOMPARE(p.prop5, 5.0);
        QCOMPARE(p.prop6, 6.0);
        QCOMPARE(p.prop7, 7.0);
        QCOMPARE(p.prop8, 8.0);
    }

    void parseParticleLineOneCharType() {
        auto p = parseParticleLine("O  4.025687 -1.261475 3.247500 3.470864");
        QCOMPARE(p.type.type, "O "); //types are 2 chars
    }

    void parseParticleLineWrongType() {
        QVERIFY_EXCEPTION_THROWN(parseParticleLine("X011 1.030e+04 1.040e+03 1.030e+04"), aviz::parse_error);
    }

    void parseParticleLineTooManyParameters() {
        QVERIFY_EXCEPTION_THROWN(parseParticleLine("X0 1.030e+04 1.040e+03 1.030e+04 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0"), aviz::parse_error);
    }

    void parseParticleLineMissingZ() {
        QVERIFY_EXCEPTION_THROWN(parseParticleLine("X0 1.030e+04 1.040e+03"), aviz::parse_error);
    }
};

QTEST_MAIN(TestFileFunctions)
#include "fileFunctionsTest.moc"
