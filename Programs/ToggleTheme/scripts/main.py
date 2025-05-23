import os
import json
import threading
import winreg
import time

from pystray import Icon, Menu, MenuItem
from PIL import Image

SCRIPT_PATH = os.environ.get('LOCALAPPDATA') + r'\ToggleTheme'
CONFIG_FILE = SCRIPT_PATH + r'\settings\settings.json'
ICON_FILE_L = SCRIPT_PATH + r'\icons\icon_1.ico'
ICON_FILE_D = SCRIPT_PATH + r'\icons\icon_0.ico'

def load_json(path):
    with open(path, 'r') as file:
        return json.load(file)

def save_json(path, data):
    with open(path, 'w') as file:
        file.write(json.dumps(data))

def change_theme(*args):
    data = load_json(CONFIG_FILE)
    if len(data['themes']) == 0:
        return
    if data['current'] is None:
        data['current'] = 0
    data['mode'] = (data['mode'] + 1) % 2
    save_json(CONFIG_FILE, data)
    os.system(f'powershell -Command "start \'{data['themes'][data['current']][str(data['mode'])]}\'"')
    time.sleep(3)

def change_walls(*args):
    data = load_json(CONFIG_FILE)
    if len(data['themes']) < 2:
        return
    if data['current'] is None:
        data['current'] = -1
    data['current'] = (data['current'] + 1) % len(data['themes'])
    save_json(CONFIG_FILE, data)
    os.system(f'powershell -Command "start \'{data['themes'][data['current']][str(data['mode'])]}\'"')
    time.sleep(3)

def theme_check(icon: Icon, closer: threading.Event):
    old_value = None
    while not closer.is_set():
        key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, r'SOFTWARE\Microsoft\Windows\CurrentVersion\Themes\Personalize')
        value = winreg.QueryValueEx(key, 'SystemUsesLightTheme')[0]
        if value != old_value:
            icon.icon = Image.open(ICON_FILE_D if value == 0 else ICON_FILE_L)
            old_value = value
        time.sleep(3)

if __name__ == '__main__':
    tray_icon = Icon('Toggler', Image.open(ICON_FILE_L), 'Toggle theme', Menu(
        MenuItem('Change theme', change_theme, default=True),
        MenuItem('Change walls', change_walls),
        MenuItem('Close', lambda *args: tray_icon.stop())
    ))
    tray_closer = threading.Event()
    threading.Thread(target=theme_check, args=[tray_icon, tray_closer], daemon=False).start()
    tray_icon.run()
    tray_closer.set()
