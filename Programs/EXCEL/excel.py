import re
import os
from utilities import Correspondences
import openpyxl
from openpyxl.worksheet.datavalidation import DataValidation


class MyWorkers:
    @staticmethod
    def regexp_worker(rules, value):
        for i in rules.keys():
            if re.search(i, value) is not None:
                return rules[i]
        return None


def add_validation(book: openpyxl.Workbook):
    sheet = book['ТИ']

    rule = DataValidation(type="list", formula1='=\'Тип ТИ\'!$A$2:$A$43', allow_blank=True)
    sheet.add_data_validation(rule)
    rule.add("G1:G1048576")

    rule = DataValidation(type="list", formula1='=\'Тип ТИ\'!$L$2:$L$16', allow_blank=True)
    sheet.add_data_validation(rule)
    rule.add("H1:H1048576")

    sheet = book['ТС']

    rule = DataValidation(type="list", formula1='=\'Тип ТИ\'!$L$2:$L$16', allow_blank=True)
    sheet.add_data_validation(rule)
    rule.add("F1:F1048576")

    rule = DataValidation(type="list", formula1='=\'Тип ТИ\'!$D$2:$D$43', allow_blank=True)
    sheet.add_data_validation(rule)
    rule.add("D1:D1048576")

    rule = DataValidation(type="list", formula1='=\'Тип ТИ\'!$I$2:$I$193', allow_blank=True)
    sheet.add_data_validation(rule)
    rule.add("E1:E1048576")

    rule = DataValidation(type="list", formula1='=\'Тип ТИ\'!$G$2:$G$6', allow_blank=True)
    sheet.add_data_validation(rule)
    rule.add("Q1:Q1048576")

    return book


def book_edit(load, save):
    tables = Correspondences.get_correspondences('rules.xlsx')
    tables['ФИ'].set_new_worker(MyWorkers.regexp_worker)

    book = add_validation(openpyxl.load_workbook(load))

    sheet = book['ТИ']  # B -> G, H
    for i in range(2, len(sheet['B'])):
        if (value := sheet[f'B{i}'].value) is None:
            break
        # sheet[f'G{i}'].value = crs.get_value('Тип ТИ', value)
        sheet[f'H{i}'].value = tables['ФИ'].find_answer(value)

    # sheet = book['ТС']  # C -> D, E
    # for i in range(2, len(sheet['C'])):
    #     if value := sheet[f'C{i}'].value is None:
    #         break
    #     sheet[f'D{i}'].value = crs.get_value('НЗ', value)
    #     sheet[f'E{i}'].value = crs.get_value('Тип ТС', value)

    book.save(save)
    book.close()


if __name__ == '__main__':
    for k in os.listdir('C:/Users/user/Desktop/Test/'):
        book_edit(f'C:/Users/user/Desktop/Test/{k}', f'C:/Users/user/Desktop/Result/{k}')
    # book_edit('C:/Users/user/Desktop/Test/ПС 35 Головино.xlsx', 'C:/Users/user/Desktop/Result/ПС 35 Головино.xlsx')
