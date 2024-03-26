
#ifndef AGGIUNGIITEM_H
#define AGGIUNGIITEM_H

#include <QDialog>
#include<QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QFormLayout>
#include <QTimer>
#include <QMessageBox>
#include "../../Model/FileH/Casa.h"
#include "../../Model/FileH/Cibo.h"
#include "../../Model/FileH/Trasporto.h"
#include "../../Model/FileH/Vestiti.h"
#include "../../Model/FileH/Libri.h"
#include "../../Model/FileH/Item.h"
#include "../../Controller/FileH/dbcontroller.h"
#include <QLayout>

class Home;
class Utenti;

class AggiungiItem : public QDialog
{
    Q_OBJECT

public:
    AggiungiItem(Home* home, std::shared_ptr<Utenti> u, QWidget *parent);
    ~AggiungiItem();
    void clearFormLayouts();
signals:
    void aggiungiClicked(const QString &additionalData);
private slots:
    void goBack();
    void onComboBoxIndexChanged(int index);
    void aggiungi(int index);
    void aggiungiWithAdditionalData();
    void hideAggiuntoLabel();
    void onPrezzoTextChanged(const QString &text);

private:
    Home* homeWindow;
    QLabel* labelConnect;
    QLabel* labelConnect2;
    QPushButton* indietro;
    QPushButton* aggiungiButton;
    QComboBox* comboBox;
    QVBoxLayout* mainLayout;
    QVBoxLayout* labelComboLayout;
    QVBoxLayout* formContainerLayout;
    QFormLayout* formLayout;
    std::shared_ptr<Utenti> utente;
    QList<QFormLayout*> formLayouts;
    QLineEdit* enome;
    QLineEdit* edescrizione;
    QLineEdit* eprezzo;
    QLineEdit* ecoloreCasa;
    QLineEdit* ecoloreVestiti;
    QLineEdit* egenereCasa;
    QLineEdit* egenereVestiti;
    QLineEdit* egenereCibo;
    QLineEdit* egenereLibri;
    QLineEdit* eautore;
    QLineEdit* eisbn;
    QLineEdit* etaglia;
    QLineEdit* edurata;

};
#endif // AGGIUNGIITEM_H

