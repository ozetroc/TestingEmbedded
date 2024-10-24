*** Variables ***
Resource                      ${KEYWORDS}
${PROMPT}                     uart:~$

*** Keywords ***
Prepare Machine
    Execute Command           $bin = ${ELF}
    Execute Command           include ${RESC}
    Create Terminal Tester    ${UART}

*** Test Cases ***
Should Boot Zephyr
    [Documentation]           Boots Zephyr on the Leon3 platform.
    [Tags]                    zephyr  uart
    Prepare Machine

    Start Emulation

    Wait For Prompt On Uart   ${PROMPT}

    Provides                  booted-zephyr

Should Print Version
    [Documentation]           Tests shell responsiveness in Zephyr on the Leon3 platform.
    [Tags]                    zephyr  uart
    Requires                  booted-zephyr

    Write Line To Uart        version
    Wait For Line On Uart     Zephyr version 3.7.0
