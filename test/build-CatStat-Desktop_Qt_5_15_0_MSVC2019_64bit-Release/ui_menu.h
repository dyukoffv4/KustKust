/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *healthLine;
    QLabel *label_2;
    QLineEdit *AttackLine;
    QLabel *label_3;
    QLineEdit *rareLine;
    QLabel *label_16;
    QLineEdit *levelLine;
    QSpacerItem *verticalSpacer_2;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QCheckBox *secondAB;
    QCheckBox *thirdAB;
    QCheckBox *firstAB;
    QSpacerItem *verticalSpacer;
    QFormLayout *formLayout_3;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QCheckBox *firstHB;
    QCheckBox *thirdHB;
    QCheckBox *secondHB;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName(QString::fromUtf8("Menu"));
        Menu->resize(585, 641);
        centralwidget = new QWidget(Menu);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        healthLine = new QLineEdit(centralwidget);
        healthLine->setObjectName(QString::fromUtf8("healthLine"));

        formLayout->setWidget(0, QFormLayout::FieldRole, healthLine);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        AttackLine = new QLineEdit(centralwidget);
        AttackLine->setObjectName(QString::fromUtf8("AttackLine"));

        formLayout->setWidget(1, QFormLayout::FieldRole, AttackLine);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        rareLine = new QLineEdit(centralwidget);
        rareLine->setObjectName(QString::fromUtf8("rareLine"));

        formLayout->setWidget(2, QFormLayout::FieldRole, rareLine);

        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_16);

        levelLine = new QLineEdit(centralwidget);
        levelLine->setObjectName(QString::fromUtf8("levelLine"));

        formLayout->setWidget(3, QFormLayout::FieldRole, levelLine);


        verticalLayout->addLayout(formLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_6);

        secondAB = new QCheckBox(centralwidget);
        secondAB->setObjectName(QString::fromUtf8("secondAB"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, secondAB);

        thirdAB = new QCheckBox(centralwidget);
        thirdAB->setObjectName(QString::fromUtf8("thirdAB"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, thirdAB);

        firstAB = new QCheckBox(centralwidget);
        firstAB->setObjectName(QString::fromUtf8("firstAB"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, firstAB);


        verticalLayout->addLayout(formLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_8);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_9);

        firstHB = new QCheckBox(centralwidget);
        firstHB->setObjectName(QString::fromUtf8("firstHB"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, firstHB);

        thirdHB = new QCheckBox(centralwidget);
        thirdHB->setObjectName(QString::fromUtf8("thirdHB"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, thirdHB);

        secondHB = new QCheckBox(centralwidget);
        secondHB->setObjectName(QString::fromUtf8("secondHB"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, secondHB);


        verticalLayout->addLayout(formLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        Menu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Menu);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 585, 26));
        Menu->setMenuBar(menubar);
        statusbar = new QStatusBar(Menu);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Menu->setStatusBar(statusbar);

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QMainWindow *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "Menu", nullptr));
        label->setText(QCoreApplication::translate("Menu", "Cat Health Initial", nullptr));
        label_2->setText(QCoreApplication::translate("Menu", "Cat Attack Initial", nullptr));
        label_3->setText(QCoreApplication::translate("Menu", "Cat Rare", nullptr));
        label_16->setText(QCoreApplication::translate("Menu", "Cat Level", nullptr));
        label_4->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        secondAB->setText(QCoreApplication::translate("Menu", "Charpter Two Attack Bonus", nullptr));
        thirdAB->setText(QCoreApplication::translate("Menu", "Charpter Three Attack Bonus", nullptr));
        firstAB->setText(QCoreApplication::translate("Menu", "Charpter One Attack Bonus", nullptr));
        label_7->setText(QString());
        label_8->setText(QString());
        label_9->setText(QString());
        firstHB->setText(QCoreApplication::translate("Menu", "Charpter One Health Bonus", nullptr));
        thirdHB->setText(QCoreApplication::translate("Menu", "Charpter Three Health Bonus", nullptr));
        secondHB->setText(QCoreApplication::translate("Menu", "Charpter Two Health Bonus", nullptr));
        pushButton->setText(QCoreApplication::translate("Menu", "Result Stat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
