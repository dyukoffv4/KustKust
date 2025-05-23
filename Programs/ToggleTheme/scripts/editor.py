import os
import json
import argparse

CONFIG_FILE = os.environ.get('LOCALAPPDATA') + r'\ToggleTheme\settings\settings.json'
THEMES_PATH = os.environ.get('LOCALAPPDATA') + r'\Microsoft\Windows\Themes'

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('theme_l', type=str)
    parser.add_argument('theme_d', type=str)
    args = parser.parse_args()

    theme_l_path = THEMES_PATH + '\\' + args.theme_l
    theme_d_path = THEMES_PATH + '\\' + args.theme_d

    if not os.path.exists(theme_l_path):
        print(f'Theme {args.theme_l} does not exist!')
        exit(1)

    if not os.path.exists(theme_d_path):
        print(f'Theme {args.theme_d} does not exist!')
        exit(1)

    with open(CONFIG_FILE, 'r+') as file:
        data = json.load(file)
        data['themes'].append({'0': theme_l_path, '1': theme_d_path})
        data['current'] = 0 if data['current'] is None else data['current']
        file.seek(0)
        file.truncate()
        file.write(json.dumps(data))
