from tests.test_base import *
from selenium.webdriver.common.action_chains import ActionChains
from utils.locators import MainPageLocators

import time


class ClearingTrashTest(BaseTest):
    def test_ClearTrash(self):
        locators = MainPageLocators(self.direct_name)
        WebDriverWait(self.driver, 10).until(EC.presence_of_element_located(locators.getByName('space')))

        state = True if len(self.driver.find_elements(*locators.getByName('test_folder'))) == 1 else False
        self.assertTrue(state, f'Clearing Trash Error: The Folder "{self.direct_name}" must exist!')

        action = ActionChains(self.driver)
        action.context_click(self.driver.find_element(*locators.getByName('test_folder')))
        action.perform()
        # check
        state = True if len(self.driver.find_elements(*locators.getByName('file_delete'))) == 1 else False
        self.assertTrue(state, 'Clearing Trash Error: Popup menu was not displayed!')

        # ---

        self.driver.find_element(*locators.getByName('file_delete')).click()
        time.sleep(5)
        # check
        state = True if len(self.driver.find_elements(*locators.getByName('test_folder'))) == 0 else False
        self.assertTrue(state, 'Clearing Trash Error: Directory was not deleted!')

        # ---

        state = True if len(self.driver.find_elements(*locators.getByName('trash_folder'))) == 1 else False
        self.assertTrue(state, 'Clearing Trash Error: The Folder "Корзина" must exist!')
        action.double_click(self.driver.find_element(*locators.getByName('trash_folder')))
        action.perform()
        # check
        state = True if len(self.driver.find_elements(*locators.getByName('trash_delete'))) == 1 else False
        self.assertTrue(state, 'Clearing Trash Error: The Folder "Корзина" does not open!')

        # ---

        self.driver.find_element(*locators.getByName('trash_delete')).click()
        time.sleep(1)
        # check
        state = True if len(self.driver.find_elements(*locators.getByName('trash_confirm_button'))) == 1 else False
        self.assertTrue(state, 'Clearing Trash Error: Confirmation window was not displayed!')

        self.driver.find_element(*locators.getByName('trash_confirm_button')).click()
        time.sleep(5)
        # check
        state = True if len(self.driver.find_elements(*locators.getByName('trash_content'))) == 0 else False
        self.assertTrue(state, 'Clearing Trash Error: Clearing went wrong!')
