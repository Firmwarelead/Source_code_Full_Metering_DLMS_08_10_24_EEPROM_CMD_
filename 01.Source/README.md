# Releases

Following are release of 1P2W Smart Meter RL78I1C (512KB), including alpha and beta versions.

## Stable Versions

### 1p-v1.0
ef725420 · Merge branch '136-reading-parameter-in-current-cycle-billing-buffer' into 'master'
Release 1p-v1.0

- Resolve "Reading parameter in current cycle billing buffer", MR !135
- Resolve "After activating passive calendar to active calendar bill should generate", MR !134
- Resolve "Activity calendar cannot find active season", MR !132
- Resolve "Process for load survey tariff max demand during neutral missing", MR !124

## Beta Versions

All known issues about reset are resolved from beta versions.

### 1p-v1.0-beta8
a9ce322f · Merge branch '118-relay-control-update-for-new-code-structure' into 'master'
Release 1p-v1.0-beta8

- Resolve "Meter is not format when invoke format command of private protocol", MR !128
- Resolve "Abnormal handling for tariff and max demand", MR !127
- Resolve "Relay control update for new code structure", MR !123
- Resolve "Implement current billing cycle", MR !122
- Resolve "Add DLMS class 47 object and link with modem info", MR !116
- Resolve "Average current calculation value is incorrect", MR !115
- Resolve "Fix wrong configuration of Obis Generator base on test result", MR !85
- Implement Total PON and Billing PON duration, MR !83
- Resolve "Link Activity calendar to new scheduler application", MR !75

### 1p-v1.0-beta7
ddfe48b6 · Merge branch '110-energy-counter-loss-after-sleep-wakeup-without-standby-calculation' into 'master'
Release 1p-v1.0-beta7

- Resolve "Abnormal case handling", MR !29
- Resolve "Porting Fibocom H310 TCP wrapper to Neoway WM620 TCP wrapper", MR !31
- Resolve "Clean up old energy app folder", MR !59
- Resolve "Implementation of empty event log reset API", MR !100
- Resolve "Case Open persistent time is not effective", MR !104
- Resolve "Event neutral missing release logged every sleep-wakeup cycle", MR !103
- Resolve "Implement ESW and ESWF for new code structure", MR !105
- Resolve "Move block load profile capture period from DLMS to Load Survey application", MR !106
- Resolve "Energy counter loss after sleep-wakeup without standby calculation", MR !107
- Resolve "Implement average power factor in load survey", MR !111

### 1p-v1.0-beta6
403b4390 · Merge branch '98-captured-persistent-time-is-faster-than-the-configuration-time' into 'master'
Release 1p-v1.0-beta6

- Resolve "No linkage for demand integration period and issue for check max demand period change", MR !81
- Resolve "Capture selected accumulation line from metrology in snapshot and share with other application", MR !94
- Resolve "Captured persistent time is faster than the configuration time", MR !95
- Resolve "rl78i1c.mtpj have warnings on build of Storage, Event, DLMS OBIS, Load Survey", MR !98
- Resolve "Failed to download object list of PC association on KakiTech Meter Explorer", MR !99
- Change Neutral missing from "transaction" (3)" to others event" group(4), MR !101
- Resolve "Implement absolute of PF value for detect Low PF event in 512K Smart Meter same as 256KB Smart Meter.", MR !102

### 1p-v1.0-beta5
995c073e · Merge branch '58-port-scheduler-application-from-i1c-512kb-1p2w-to-3p4w-smart-meter' into 'master'
Release 1p-v1.0-beta5

- Resolve "Not check any more for schedule if it was hit one time", MR !79
- Resolve "Link new load survey to DLMS OBIS selective access function", MR !86

### 1p-v1.0-beta4
4fd0e3f9 · Merge branch '96-case-open-event-is-logged-when-power-cycle-happen-on-off-on' into 'master'
Release 1p-v1.0-beta4

- Resolve "Load survey Average Voltage and Average current", MR !76
- Resolve "TAU02 does not run after DLMS time out wrapper call TIMEOUT_DEVICE_Init, causing metrology for current does not run.", MR !82
- Resolve "Convert rtc value from bcd to dec", MR !89
- Resolve "Check instantaneous snapshot power factor usage", MR !92
- Resolve "Case Open event is logged when power cycle happen (on, off, on)", MR !96

### 1p-v1.0-beta3
5918ba4b · Merge branch '73-backup-last-instantaneous-snapshot-pop-out-value' into 'master'
Release 1p-v1.0-beta3

- Resolve "Backup last instantaneous snapshot pop out value", MR !72
- Resolve "Wrong linkage for logical device name and device ID", MR !78

### 1p-v1.0-beta2
16cf3ff6 · Merge branch '69-move-billing-counter-into-load-survey-appication' into 'master'
Release 1p-v1.0-beta2

- Resolve "Implement scheduler checking for tariff and max demand", MR !62
- Resolve "Change storing value of OBIS object's attribute to RAM then backup to EEPROM as default", MR !67
- Resolve "Move billing counter into load survey application", MR !69
- Resolve "Missing linkage data for daily load period class 07 attribute 04", MR !70 and !74
- Resolve "Fix link wrong event for set RTC and add linkage for set_billing_dates", MR !71

### 1p-v1.0-beta1
53542654 · Merge branch '50-update-eeprom-storage-map' into 'master'
Release 1p-v1.0-beta1

- Resolve "Move nameplate to meter Dataflash", MR !49
- Resolve "LCD refresh not correct 0.5s", MR !60

## Alpha Versions

Reset issues are known and existed somewhere in alpha versions.

### 1p-v1.0-alpha5
71dc7add · Merge branch '68-lcd-display-energy-total-values' into 'master'
Release 1p-v1.0-alpha5

- Resolve "Meter reset when press LCD scroll button continuously and quickly.", MR !64
- Resolve "LCD display Energy total values", MR !68

### 1p-v1.0-alpha4
9c86dce6 · Merge branch '41-lack-persistent-time-for-case-open-event-flag' into 'master'
Release 1p-v1.0-alpha4

- Resolve "Lack Persistent time for Case Open event flag.", MR !41

### 1p-v1.0-alpha3
e6cde235 · Merge branch...
Release 1p-v1.0-alpha3

- Resolve "Pointer of execution time in Scheduler application is NULL", MR !53
- Resolve "Fixing for start meter data format of EEPROM that it must be reserved for Energy counter", MR !47

### v1.0-alpha2
43cbf307 · Merge branch '53-remove-r_dlms_storage_table-c-file' into 'master'
Release 1p-v1.0-alpha2

- Resolve "Wrong starting address define for DLMS storage format", MR !45
- Resolve "Missed clear EEPROM data of meter(includes application for simple meter) in format function.", MR !46
- Resolve "Mistake of Event backup(typo)", MR !48
- Resolve "Change linkage of tamper counter for OBIS code.", MR !50
- Resolve "Wrong linkage for device ID", MR !51
- Resolve "Remove r_dlms_storage_table.c file", MR !52

### v1.0-alpha1
f1241fc5 · Merge branch...
Release 1p-v1.0-alpha1

- Resolve "Fixing missing write default value for energy app in format function", MR !38
- Resolve "Fixing for wrong mapping storage pointer link variable of DLMS event.", MR !39
- Resolve "Wrong definition for energy tariff format storage data", MR !40
- Resolve "Miss-match selected object type in buffer content(attribute 02 class 07) with original object of event related current, voltage and others", MR !42
- Resolve "[Event] Wrong backup size of g_event_state", MR !43
- Resolve "Change number of day profile and action inside each day profile to fit 512 bytes causing new define in DLMS lib.", MR !44

### v1.0-alpha
acdfd9b2 · Merge branch '37-lcd-does-not-refresh-immediately-when-the-button-is-pressed' into 'master'
Release 1p-v1.0-alpha 

# Initialized by below repo

https://gitlab.rvc.renesas.com/KSS/EM_RL78I1C_1P2W_SmartMeter2/-/tree/242-integration-phase3-dlms-enabled-full-meter-workspace/Source
