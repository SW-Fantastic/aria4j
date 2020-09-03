package org.swdc.aria2;

public enum DEventType {

    BEGIN(1),PAUSED(2),STOP(3),COMPLETE(4),ERROR(5),BT_COMPLETE(6);

    public static DEventType getType(int val) {
        switch (val) {
            case 1:
                return BEGIN;
            case 2:
                return PAUSED;
            case 3:
                return STOP;
            case 4:
                return COMPLETE;
            case 5:
                return ERROR;
            case 6:
                return BT_COMPLETE;
        }
        return null;
    }

    private int nativeState;

    DEventType(int val) {
        nativeState = val;
    }

}
