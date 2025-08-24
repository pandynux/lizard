import questionary
import os
from pathlib import Path
import argparse
import shutil

def run_interactive_mode():
    """Runs the generator in interactive mode."""
    print("ESP-IDF Interactive Project Generator")
    print("------------------------------------")

    project_name = questionary.text(
        "What is the name of your project?",
        validate=lambda text: True if len(text) > 0 and not os.path.exists(text) else "Please enter a valid name for a new directory."
    ).ask()

    if not project_name:
        print("Project creation cancelled.")
        return None

    target_chip = questionary.select(
        "Select your target chip:",
        choices=['esp32', 'esp32s2', 'esp32s3', 'esp32c3', 'esp32c6', 'esp32h2', 'esp32p4']
    ).ask()

    use_wifi = questionary.confirm("Do you need Wi-Fi?", default=True).ask()

    bt_choice = questionary.select(
        "Select Bluetooth stack:",
        choices=[
            "None",
            "BLE (NimBLE - for low memory usage)",
            "BLE + Classic (Bluedroid - dual-mode)"
        ],
        default="None"
    ).ask()

    log_level = questionary.select(
        "Select default log level:",
        choices=[
            ("Info", "INFO"),
            ("Debug", "DEBUG"),
            ("Verbose", "VERBOSE"),
            ("Warning", "WARN"),
            ("Error", "ERROR"),
            ("None", "NONE")
        ],
        default="Info"
    ).ask()

    return {
        "project_name": project_name,
        "target_chip": target_chip,
        "use_wifi": use_wifi,
        "bt_choice": bt_choice,
        "log_level": log_level,
    }

def run_non_interactive_mode(args):
    """Runs the generator using command-line arguments."""
    print("ESP-IDF Non-Interactive Project Generator")
    print("---------------------------------------")
    if not args.project_name or os.path.exists(args.project_name):
        raise ValueError("A valid, new project name is required.")

    return {
        "project_name": args.project_name,
        "target_chip": args.chip,
        "use_wifi": args.wifi,
        "bt_choice": args.bt,
        "log_level": args.log_level,
    }

def main():
    """
    Main function to run the interactive project generator.
    """
    parser = argparse.ArgumentParser(description="ESP-IDF Project Generator")
    parser.add_argument("--non-interactive", action="store_true", help="Run in non-interactive mode.")
    parser.add_argument("--project-name", type=str, help="Name of the project.")
    parser.add_argument("--chip", type=str, default="esp32", choices=['esp32', 'esp32s2', 'esp32s3', 'esp32c3', 'esp32c6', 'esp32h2', 'esp32p4'])
    parser.add_argument("--wifi", action=argparse.BooleanOptionalAction, default=True)
    parser.add_argument("--bt", type=str, default="None", choices=["None", "NimBLE", "Bluedroid"])
    parser.add_argument("--log-level", type=str, default="INFO", choices=["INFO", "DEBUG", "VERBOSE", "WARN", "ERROR", "NONE"])
    args = parser.parse_args()

    if args.non_interactive:
        config = run_non_interactive_mode(args)
    else:
        config = run_interactive_mode()

    if not config:
        return # User cancelled in interactive mode

    project_name = config["project_name"]
    target_chip = config["target_chip"]
    use_wifi = config["use_wifi"]
    bt_choice = config["bt_choice"]
    log_level = config["log_level"]

    # --- Generation Logic ---
    print("\nGenerating project structure...")
    try:
        project_path = Path(project_name)
        main_path = project_path / "main"
        main_path.mkdir(parents=True)
        print(f"Created directory: {main_path}")

        # --- Generate sdkconfig.defaults ---
        sdkconfig_content = generate_sdkconfig(use_wifi, bt_choice, log_level)
        (project_path / "sdkconfig.defaults").write_text(sdkconfig_content)
        print("Created sdkconfig.defaults")

        # --- Generate main/main.c ---
        main_c_content = generate_main_c(use_wifi, bt_choice)
        (main_path / "main.c").write_text(main_c_content)
        print("Created main/main.c")

        # --- Generate CMakeLists.txt files ---
        (project_path / "CMakeLists.txt").write_text(get_root_cmakelists(project_name))
        print("Created CMakeLists.txt")
        (main_path / "CMakeLists.txt").write_text(get_main_cmakelists())
        print("Created main/CMakeLists.txt")

        print("\n--- Project Generation Complete! ---")
        print(f"Project '{project_name}' created successfully.")
        print("\nNext Steps:")
        print(f"1. cd {project_name}")
        print(f"2. idf.py set-target {target_chip}")
        print("3. idf.py menuconfig (to review and customize further)")
        print("4. idf.py build")
        print("------------------------------------")

    except Exception as e:
        print(f"\nAn error occurred: {e}")
        # Clean up created directory if something went wrong
        if 'project_path' in locals() and project_path.exists():
            import shutil
            shutil.rmtree(project_path)
            print(f"Cleaned up directory {project_path}")

def generate_sdkconfig(use_wifi, bt_choice, log_level):
    """Generates the content for sdkconfig.defaults based on user choices."""
    lines = ["# SDK Config Defaults Generated by idf_project_generator.py", ""]

    # Log Level
    lines.append(f"CONFIG_LOG_DEFAULT_LEVEL_{log_level}=y")
    lines.append("")

    # Wi-Fi
    if use_wifi:
        lines.append("# Enable Wi-Fi")
        lines.append("CONFIG_ESP_WIFI_ENABLED=y")
        lines.append("")

    # Bluetooth
    if "NimBLE" in bt_choice:
        lines.append("# Enable Bluetooth (BLE Only - NimBLE)")
        lines.append("CONFIG_BT_ENABLED=y")
        lines.append("CONFIG_BT_NIMBLE_ENABLED=y")
        lines.append("")
    elif "Bluedroid" in bt_choice:
        lines.append("# Enable Bluetooth (Dual Mode - Bluedroid)")
        lines.append("CONFIG_BT_ENABLED=y")
        lines.append("CONFIG_BT_BLUEDROID_ENABLED=y")
        lines.append("")

    return "\n".join(lines)

def generate_main_c(use_wifi, bt_choice):
    """Generates a boilerplate main.c file with necessary includes."""
    includes = [
        '#include <stdio.h>',
        '#include "freertos/FreeRTOS.h"',
        '#include "freertos/task.h"',
        '#include "esp_log.h"',
    ]
    if use_wifi:
        includes.append('#include "esp_wifi.h"')
    if bt_choice != "None":
        includes.append('#include "esp_bt.h"')

    # Ensure no duplicate includes
    includes = sorted(list(set(includes)))

    body = f"""
static const char *TAG = "main";

void app_main(void)
{{
    ESP_LOGI(TAG, "Project Initialized!");

    // Your application code goes here.
    // For example, initialize Wi-Fi, Bluetooth, or other components.

    while (1) {{
        vTaskDelay(pdMS_TO_TICKS(1000));
    }}
}}
"""
    return "\n".join(includes) + body

def get_root_cmakelists(project_name):
    """Returns the content for the root CMakeLists.txt file."""
    return f'''# This file was generated by idf_project_generator.py
cmake_minimum_required(VERSION 3.16)
include(${{IDF_PATH}}/tools/cmake/project.cmake)
project({project_name})
'''

def get_main_cmakelists():
    """Returns the content for the main/CMakeLists.txt file."""
    return '''# This file was generated by idf_project_generator.py
idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS ".")
'''


if __name__ == "__main__":
    main()
