from selenium.webdriver.common.by import By


class PageLocators:
    def __init__(self):
        self.data: dict = {}

    def getByName(self, name) -> set:
        if self.data[name]:
            return self.data[name]


class LoginPageLocators(PageLocators):
    def __init__(self):
        super().__init__()
        self.data = {
            'submit': (By.XPATH, '//button[@type="submit"]'),
            'username': (By.NAME, 'login'),
            'password': (By.NAME, 'passwd'),
            'e_button': (By.XPATH, '//div[@class="AuthLoginInputToggle-wrapper"]//button[1]')
        }


class MainPageLocators(PageLocators):
    def __init__(self, folder_name):
        super().__init__()
        self.data = {
            'space': (By.CLASS_NAME, 'root__content-container'),
            'file_adding': (By.XPATH, '//div[@class="Menu-Group"]//div[@value="new-folder"]'),
            'confirm_name': (By.XPATH, '//div[@class="confirmation-dialog__content"]//input'),
            'confirm_submit': (By.XPATH, '//div[@class="confirmation-dialog__footer"]//button'),
            'test_folder': (By.XPATH, f'//div[@class="listing__items"]//div[@aria-label="{folder_name}"]'),
            'file_delete': (By.XPATH, '//div[@class="resources-actions-popup__wrapper"]//div[@value="delete"]'),
            'trash_folder': (By.XPATH, '//div[@class="listing__items"]//div[@aria-label="Корзина"]'),
            'trash_delete': (By.XPATH, '//div[@class="listing-head__additional-actions"]//button[1]'),
            'trash_confirm_button': (By.XPATH, '//div[@class="confirmation-dialog__footer"]//button[2]'),
            'trash_content': (By.XPATH, '//div[@class="listing__items"]//div[@class="listing-item__info"]')
        }
