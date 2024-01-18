#include <math.h>
#include <stdio.h>

const double REGULAR_POSTCARD_PRICE_PER_POUND = 0.20 / 0.0625;
const double LARGE_POSTCARD_PRICE_PER_POUND = 0.30 / 0.0625;
const double ENVELOPE_PRICE_PER_POUND = 0.47 / 0.0625;
const double LARGE_ENVELOPE_PRICE_PER_POUND = 0.56 / 0.0625;
const double PACKAGE_PRICE_PER_POUND = 1.50 / 0.50;
const double LARGE_PACKAGE_PRICE_PER_POUND = 1.75 / 0.50;

const double REGULAR_POSTCARD_INTERVAL = 0.20;
const double LARGE_POSTCARD_INTERVAL = 0.30;
const double ENVELOPE_INTERVAL = 0.47;
const double LARGE_ENVELOPE_INTERVAL = 0.56;
const double PACKAGE_INTERVAL = 1.50;
const double LARGE_PACKAGE_INTERVAL = 1.75;

enum PostageType {
    RegularPostcard,
    LargePostcard,
    Envelope,
    LargeEnvelope,
    Package,
    LargePackage,
    Unmailable,
};

struct Postage {
    double length;
    double height;
    double thickness;
    double weight;
};

int isBetweenInclusive(double num, double min, double max) {
    return num >= min && num <= max;
}

int isBetween(double num, double min, double max) {
    return num > min && num < max;
}

int isRegularPostcard(struct Postage postage) {
    return isBetweenInclusive(postage.length, 3.5, 4.25) &&
           isBetweenInclusive(postage.height, 3.5, 6) &&
           isBetweenInclusive(postage.thickness, 0.007, 0.016);
}

int isLargePostcard(struct Postage postage) {
    return isBetween(postage.length, 4.25, 6) &&
           isBetween(postage.height, 6, 11.5) &&
           isBetweenInclusive(postage.thickness, 0.007, 0.016);
}

int isEnvelope(struct Postage postage) {
    return isBetweenInclusive(postage.length, 3.5, 6.125) &&
           isBetweenInclusive(postage.height, 5, 11.5) &&
           isBetweenInclusive(postage.thickness, 0.016, 0.25);
}

int isLargeEnvelope(struct Postage postage) {
    return isBetween(postage.length, 6.125, 24) &&
           isBetweenInclusive(postage.height, 11, 18) &&
           isBetweenInclusive(postage.thickness, 0.25, 0.5);
}

int exceedsLargeEnvelope(struct Postage postage) {
    return (postage.length >= 24 || postage.height > 18 ||
            postage.thickness > 0.5);
}

int isPackage(struct Postage postage) {
    if (!exceedsLargeEnvelope(postage)) {
        return 0;
    }

    double girth = 2 * (postage.height + postage.thickness);
    return postage.length + girth <= 84;
}

int isLargePackage(struct Postage postage) {
    if (!exceedsLargeEnvelope(postage)) {
        return 0;
    }

    double girth = 2 * (postage.height + postage.thickness);
    double packageSize = postage.length + girth;
    return packageSize > 84 && packageSize <= 130;
}

enum PostageType getPostageType(struct Postage postage) {
    if (isRegularPostcard(postage)) {
        return RegularPostcard;
    }
    if (isLargePostcard(postage)) {
        return LargePostcard;
    }
    if (isEnvelope(postage)) {
        return Envelope;
    }

    if (isLargeEnvelope(postage)) {
        return LargeEnvelope;
    }
    if (isPackage(postage)) {
        return Package;
    }
    if (isLargePackage(postage)) {
        return LargePackage;
    }

    return Unmailable;
}

double getPostagePrice(struct Postage postage, enum PostageType postageType) {
    double pricePerPound = 0;
    double interval = 1;

    switch (postageType) {
    case RegularPostcard:
        pricePerPound = REGULAR_POSTCARD_PRICE_PER_POUND;
        interval = REGULAR_POSTCARD_INTERVAL;
        break;
    case LargePostcard:
        pricePerPound = LARGE_POSTCARD_PRICE_PER_POUND;
        interval = LARGE_POSTCARD_INTERVAL;
        break;
    case Envelope:
        pricePerPound = ENVELOPE_PRICE_PER_POUND;
        interval = ENVELOPE_INTERVAL;
        break;
    case LargeEnvelope:
        pricePerPound = LARGE_ENVELOPE_PRICE_PER_POUND;
        interval = LARGE_ENVELOPE_INTERVAL;
        break;
    case Package:
        pricePerPound = PACKAGE_PRICE_PER_POUND;
        interval = PACKAGE_INTERVAL;
        break;
    case LargePackage:
        pricePerPound = LARGE_PACKAGE_PRICE_PER_POUND;
        interval = LARGE_PACKAGE_INTERVAL;
        break;
    case Unmailable:
        return -1;
        break;
    }

    return ceil(postage.weight * pricePerPound / interval) * interval;
}

char* to_string(enum PostageType type) {
    switch (type) {
    case RegularPostcard:
        return "Regular Postcard";
    case LargePostcard:
        return "Large Postcard";
    case Envelope:
        return "Envelope";
    case LargeEnvelope:
        return "Large Envelope";
    case Package:
        return "Package";
    case LargePackage:
        return "Large Package";
    case Unmailable:
        return "Unmailable";
    }
}

int main() {

    char line[1024];
    printf("Enter the package length, height, thickness, and weight <in that "
           "order>: ");
    fgets(line, 1024, stdin);

    double length;
    double height;
    double thinkness;
    double weight;

    sscanf(line, "%lf %lf %lf %lf", &length, &height, &thinkness, &weight);

    struct Postage postage = {length, height, thinkness, weight};
    enum PostageType postageType = getPostageType(postage);

    if (postageType == Unmailable) {
        printf("Your postage is Unmailable!\n");
        // system("pause");
        //
        return 0;
    }

    double price = getPostagePrice(postage, postageType);

    printf("You are mailing a(n) %s.\n", to_string(postageType));
    printf("Cost: $%.2f\n", price);

    // system("pause")

    return 0;
}
