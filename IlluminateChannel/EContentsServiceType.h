enum class EContentsServiceType {
    Closed,
    CBT,
    Pre,
    OBT,
    Commercial

    /*
        private byte id;

    EContentsServiceType(final int id) {
        this.id = (byte) id;
    }

    public static EContentsServiceType valueOf(final int reqType) {
        if (reqType < 0 || reqType > values().length - 1) {
            return null;
        }
        return values()[reqType];
    }
    */
};