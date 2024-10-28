*** Settings ***
Library     Process
Library     SerialLibrary    encoding=ascii

*** Variables ***
${PROMPT}                     uart:~$
${UART2}                      /dev/ttyACM0
${ELF}                        twister-out/controller_l432kc_stm32l432xx/app.robot_hw/zephyr/zephyr.hex
${UNDER_RESET}                connect_mode=under-reset

*** Keywords ***
Prepare Machine

    SerialLibrary.Add Port    ${UART2}
    ...        baudrate=115200
    ...        bytesize=8
    ...        parity=N
    ...        stopbits=1
    ...        encoding=ascii
    SerialLibrary.Open Port   ${UART2}
    SerialLibrary.Port Should Be Open    ${UART2}

    ${result} =    Run Process               west   flash   
    Log to console             ${result.stdout}
    Should Not Contain    ${result.stdout}    FAIL



*** Test Cases ***
Should Boot Zephyr
    [Documentation]           Boots Zephyr on the controller_l432kc physical platform.
    [Tags]                    zephyr  uart
    Prepare Machine

    Sleep             20s
    ${response}=      Read All Data    encoding=ascii
    Should Contain    ${response}      Booting Zephyr OS build v3.7.0
    Should Contain    ${response}      PASS

    [Teardown]    Delete All Ports

