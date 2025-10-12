from tests.test_base import *
from selenium.webdriver.common.action_chains import ActionChains
from utils.locators import MainPageLocators

import time


class AddingDirectoryTest(BaseTest):
    def test_AddDirectory(self):
        locators = MainPageLocators(self.direct_name)
        WebDriverWait(self.driver, 10).until(EC.presence_of_element_located(locators.getByName('space')))

        action = ActionChains(self.driver)
        action.context_click(self.driver.find_element(*locators.getByName('space')))
        action.perform()
        # check
        state = True if len(self.driver.find_elements(*locators.getByName('file_adding'))) == 1 else False
        self.assertTrue(state, 'Adding Directory Error: Popup menu was not displayed!')

        # ---

        self.driver.find_element(*locators.getByName('file_adding')).click()
        time.sleep(1)
        # check
        state = True if len(self.driver.find_elements(*locators.getByName('confirm_name'))) == 1 else False
        self.assertTrue(state, 'Adding Directory Error: Confirmation window was not displayed!')

        # ---

        self.driver.find_element(*locators.getByName('confirm_name')).send_keys(self.direct_name)
        time.sleep(1)
        self.driver.find_element(*locators.getByName('confirm_submit')).click()
        time.sleep(1)
        # check
        state = True if len(self.driver.find_elements(*locators.getByName('test_folder'))) == 1 else False
        self.assertTrue(state, f'Adding Directory Error: Directory "{self.direct_name}" does not exist!')
