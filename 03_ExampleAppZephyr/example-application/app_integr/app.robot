*** Variables ***
Resource                      ${KEYWORDS}
${PROMPT}                     uart:~$
${RESC2}                      @/home/embedded/EmbeddedTesting/TestingEmbedded/03_ExampleAppZephyr/example-application/boards/sii/controller_l432kc/support/renode.resc
${UART2}                      sysbus.usart2

*** Keywords ***
Prepare Machine
    Execute Command           $bin = ${ELF}
    Execute Command           include ${RESC2}
    Create Terminal Tester    ${UART2}

*** Test Cases ***
Should Boot Zephyr
    [Documentation]           Boots Zephyr on the controller_l432kc platform.
    [Tags]                    zephyr  uart
    Prepare Machine

    Start Emulation

    Wait For Prompt On Uart   LockerDriver Initialized
    Execute Command           p
    ${result}=  Execute Command           sysbus.gpioa.pwrsw State
    Should Contain    ${result}    True
    ${result}=  Execute Command           sysbus.gpioa.muxen1 State
    Should Contain    ${result}    True
    ${result}=  Execute Command           sysbus.gpioa.muxen2 State
    Should Contain    ${result}    True
    ${result}=   Execute Command           sysbus.gpioa.muxs1 State
    Should Contain    ${result}    False
    ${result}=   Execute Command           sysbus.gpioa.muxs2 State
    Should Contain    ${result}    False
    ${result}=   Execute Command           sysbus.gpiob.muxs3 State
    Should Contain    ${result}    False
    ${result}=  Execute Command           sysbus.gpioa.muxs4 State
    Should Contain    ${result}    False
    ${result}=  Execute Command           sysbus.gpiob.muxcom State
    Execute Command           s

    #Should Not Be On Uart           FAIL  timeout=20

    Provides                  booted-zephyr

