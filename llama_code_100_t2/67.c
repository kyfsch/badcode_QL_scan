// This function is used to assign the LED_SERIAL output channel to the specified portmask..
rtk_api_ret_t rtk_led_serialModePortmask_get(rtk_led_serialOutput_t *pOutput, rtk_portmask_t *pPortmask)
{
    RtkWiFiMCSBoard *prx = NULL;

    /* Check if the portmask is available */
    ASSERT((sizeof(rtk_board_info[0].Portmask_LedSerial)!=sizeof(rtk_portmask_t)) || (pPortmask==NULL));

    /* Check if board is MCX in useage of this API */
    prx = (RtkWiFiMCSBoard*)_rtk_wifi_virtual_if_MCX.board;

    if (prx)
    {
        /* Get the portmask by the current used channel number */
        *pPortmask = (rtk_portmask_t)(prx->Portmask_LedSerial);
    }
    else
    {
        // TODO: throw an error
    }

    return RT_ERR_OK;
}

/* Sets portmask for specified output channel.
 * Parameters:
 *		portmask   : port number mask to be set.
 * Returns:
 *	TRUE if successful, FALSE if not.
 */
rtk_api_ret_t rtk_led_serialPortmask_set(rtk_portmask_t portmask)
{
    RtkWiFiMCSBoard *prx = NULL;

    /* Check if the portmask is available */
    ASSERT((sizeof(rtk_board_info[0].Portmask_LedSerial)!=sizeof(rtk_portmask_t)) || (portmask==0));

    prx = (RtkWiFiMCSBoard*)_rtk_wifi_virtual_if_MCX.board;

    if(prx)
    {
        /* Save the PortMask */
        prx->Portmask_LedSerial = portmask;
    }
    else
    {
        // TODO: throw an error
    }

    return RT_ERR_OK;
}

/* Gets portmask for specified output channel.
 * Parameters:
 *		pPortmask   : output the port mask
 * Returns:
 *	RT_ERR_