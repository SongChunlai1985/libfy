#include "msxlsx.h"

msxlsx::msxlsx()
{

}

QList<QVariantList> msxlsx::read(QString xlsxFileName)
{
    QList<QVariantList> Table;
    xlsxioreader xlsxioread = xlsxioread_open(xlsxFileName.toStdString().c_str());                              //open .xlsx file for reading
    if (xlsxioread == nullptr) {
        qDebug() << __FUNCTION__ << "Error opening .xlsx file\n";
        return Table;
    }

    char* value;                                                                                                //read values from first sheet
    xlsxioreadersheet sheet;
    const char* sheetname = nullptr;
    qDebug() << "Contents of first sheet:\n";
    if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != nullptr) {        //read all rows

        while (xlsxioread_sheet_next_row(sheet)) {                                                              //read all columns

            QVariantList row;
            while ((value = xlsxioread_sheet_next_cell(sheet)) != nullptr) {
                row.push_back(value);
            }
            Table.push_back(row);
            qDebug() << __FUNCTION__ << row << "\n";
        }
        xlsxioread_sheet_close(sheet);
    }

    xlsxioread_close(xlsxioread);
    return Table;
}

QVariantList msxlsx::sheetList(QString xlsxFileName)
{
    //open .xlsx file for reading
    QVariantList sheets;
    xlsxioreader xlsxioread;
    if ((xlsxioread = xlsxioread_open(xlsxFileName.toLocal8Bit().constData())) == nullptr) {
        qDebug() << __FUNCTION__ << "Error opening .xlsx file\n";
        return sheets;
    }

    //list available sheets
    xlsxioreadersheetlist sheetlist;
    const char* sheetname;
    qDebug() << __FUNCTION__ << "Available sheets:\n";
    if ((sheetlist = xlsxioread_sheetlist_open(xlsxioread)) != nullptr) {
        while ((sheetname = xlsxioread_sheetlist_next(sheetlist)) != nullptr) {
            qDebug() << __FUNCTION__ << sheetname;
        }
        xlsxioread_sheetlist_close(sheetlist);
    }

    //clean up
    xlsxioread_close(xlsxioread);
    return sheets;
}

void msxlsx::write(QString xlsxFileName, QList<QVariantList> table)
{
    //open .xlsx file for writing (will overwrite if it already exists)
    xlsxiowriter handle;
    if ((handle = xlsxiowrite_open(xlsxFileName.toLocal8Bit().constData(), "Sheet1")) == nullptr) {
        qDebug() << __FUNCTION__ << "Error creating .xlsx file\n";
        return;
    }

    foreach (QVariantList row, table) {
        foreach (QVariant cell, row) {
            xlsxiowrite_add_cell_string(handle, cell.toString().toStdString().c_str());
        }
        xlsxiowrite_next_row(handle);
    }
 /*
    //write column names
    xlsxiowrite_add_column(handle, "Col1", 16);
    xlsxiowrite_add_column(handle, "Col2", 0);
    xlsxiowrite_next_row(handle);

    //write data
    int i;
    for (i = 0; i < 1000; i++) {
        xlsxiowrite_add_cell_string(handle, "Test");
        xlsxiowrite_add_cell_int(handle, i);
        xlsxiowrite_next_row(handle);
    }
*/
    //close .xlsx file
    xlsxiowrite_close(handle);
}

