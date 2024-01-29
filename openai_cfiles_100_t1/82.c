
void sendDLLInformationToArc(unsigned int mailboxAddress, unsigned int dllInformation)
{
    // Write the DLL information to the mailbox address
    *((unsigned int*)mailboxAddress) = dllInformation;
}
