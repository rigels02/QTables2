#ifndef CSVEXPOIMPODLG_H
#define CSVEXPOIMPODLG_H

#include <QDialog>

namespace Ui {
class CsvExpoImpoDlg;
}

class CsvExpoImpoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CsvExpoImpoDlg(QWidget *parent = 0);
    ~CsvExpoImpoDlg();

    QString getDelimitersInfo();

private:
    Ui::CsvExpoImpoDlg *ui;
};

#endif // CSVEXPOIMPODLG_H
