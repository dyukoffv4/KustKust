import unittest

from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

from utils.user import USERNAME, PASSWORD, DIR_NAME
from utils.locators import LoginPageLocators


class BaseTest(unittest.TestCase):
    def setUp(self):
        self.direct_name = DIR_NAME
        self.driver = webdriver.Chrome()
        self.driver.get('https://disk.yandex.ru/client/disk')
        locators = LoginPageLocators()

        # email type choosing
        self.driver.find_element(*locators.getByName('e_button')).click()
        WebDriverWait(self.driver, 10).until(EC.presence_of_element_located(locators.getByName('username')))

        # username input
        self.driver.find_element(*locators.getByName('username')).send_keys(USERNAME)
        self.driver.find_element(*locators.getByName('submit')).click()
        WebDriverWait(self.driver, 10).until(EC.presence_of_element_located(locators.getByName('password')))

        # password input
        self.driver.find_element(*locators.getByName('password')).send_keys(PASSWORD)
        self.driver.find_element(*locators.getByName('submit')).click()

    def tearDown(self):
        self.driver.close()
        self.driver.quit()
