#!/bin/bash
set -e

SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"

VISIONAI_PRJ_PATH="$SCRIPTPATH/Synopsys_PA8535_EM9D_DFSS_SDK_3.3/app/scenario_app/edge_impulse_visionai"
SENSECAP_PRJ_PATH="$SCRIPTPATH/Synopsys_PA8535_EM9D_DFSS_SDK_3.3/app/scenario_app/edge_impulse_sensecap"

VISIONAI_MODEL_PATH="$VISIONAI_PRJ_PATH/ei-model"
SENSECAP_MODEL_PATH="$SENSECAP_PRJ_PATH/ei-model"

echo "Removing edge-impulse-sdk"
rm -rf $VISIONAI_MODEL_PATH/edge-impulse-sdk/
rm -rf $SENSECAP_MODEL_PATH/edge-impulse-sdk/
echo "Removing edge-impulse-sdk OK"

echo "Copying new version of EI SDK"
cp -r $SCRIPTPATH/../edge-impulse-sdk $VISIONAI_MODEL_PATH/edge-impulse-sdk/
cp -r $SCRIPTPATH/../edge-impulse-sdk $SENSECAP_MODEL_PATH/edge-impulse-sdk/
echo "Copying new version of EI SDK OK"

#TODO: currently we use stripped fw-sdk, see: https://github.com/edgeimpulse/edgeimpulse/issues/5914
# echo "Removing firmware-sdk"
# rm -rf $VISIONAI_PRJ_PATH/firmware-sdk/
# rm -rf $SENSECAP_PRJ_PATH/firmware-sdk/
# echo "Removing firmware-sdk OK"

# echo "Copying new version of Firmware SDK"
# cp -r $SCRIPTPATH/../firmware-sdk $VISIONAI_PRJ_PATH/firmware-sdk/
# rm $VISIONAI_PRJ_PATH/firmware-sdk/ei_fusion.*
# rm $VISIONAI_PRJ_PATH/firmware-sdk/sensor_aq.*
# cp -r $SCRIPTPATH/../firmware-sdk $SENSECAP_PRJ_PATH/firmware-sdk/
# rm $SENSECAP_PRJ_PATH/firmware-sdk/ei_fusion.*
# rm $SENSECAP_PRJ_PATH/firmware-sdk/sensor_aq.*
# echo "Copying new version of Firmware SDK OK"
