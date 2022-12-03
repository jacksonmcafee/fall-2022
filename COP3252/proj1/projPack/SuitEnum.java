package projPack;

public enum SuitEnum {
    Spades(true),
    Hearts(false),
    Diamonds(true),
    Clubs(false);

    private final boolean isBlack;
    private SuitEnum(final boolean isBlack) { this.isBlack = isBlack; }
    public boolean isBlack() { return isBlack; }
}