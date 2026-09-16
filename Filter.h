#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>
#include <stdlib.h>
// ================= Interface =================
class FilterStrategy {
public:
    virtual float apply(float input) = 0;
    virtual void reset() = 0;
    virtual ~FilterStrategy() {}
};

// ================= Identity Filter =================
class IdentityFilter : public FilterStrategy {
public:
    float apply(float input) override {
        return input;
    }

    void reset() override {}
};

// ================= EMA Filter =================
class EMAFilter : public FilterStrategy {
private:
    float alpha;
    float last;
    bool initialized = false;
public:
    EMAFilter(float a = 0.2f) : alpha(a), last(0.0f) {}

    float apply(float input) override {
        if (!initialized) {
            last = input;
            initialized = true;
        }
        last = alpha * input + (1.0f - alpha) * last;
        return last;
    }

    void reset() override {
        initialized = false;
        last = 0;
    }
};

// ================= StallFilter ==============
/*
class StallFilter : public FilterStrategy {
private:
    float last;
    float threshold;
    int stallCounter = 0;
    int stallLimit;
    bool initialized = false;

public:
    StallFilter(float t = 0.05f, int limit = 5) : threshold(t), last(0.0f), stallLimit(limit) {}

    float apply(float input) override {
        if (!initialized) {
            last = input;
            initialized = true;
            return 0.0f;
        }

        float diff = abs(input - last);
        last = input;

        if (diff < threshold) {
            stallCounter++;
        } else {
            stallCounter = 0;
        }

        return (stallCounter >= stallLimit) ? 1.0f : 0.0f;
    }

    void reset() override {
        initialized = false;
        stallCounter = 0;
    }
};
*/
class StallFilter : public FilterStrategy {
private:
    float alpha;
    float lastFiltered;
    bool initialized;

    float threshold;           // ?????? ????? ???? ????
    int stableCount;           // ??? ????? ????? ???? ?????
    int stableThreshold;       // ?????? ????? ?????

    bool stallDetected;

public:
    StallFilter(float a = 0.1f, float thresh = 0.01f, int stableThresh = 1)
        : alpha(a), lastFiltered(0), initialized(false),
          threshold(thresh), stableCount(0), stableThreshold(stableThresh),
          stallDetected(false) {}

    float apply(float input) override {
        float filtered;

        if (!initialized) {
            lastFiltered = input;
            initialized = true;
            stableCount = 0;
            stallDetected = false;
            return input;
        }

        filtered = alpha * input + (1.0f - alpha) * lastFiltered;
        float delta = abs(filtered - lastFiltered);

        if (delta < threshold) {
            stableCount++;
        } else {
            stableCount = 0;  // ???? ???? ??? ? ????? ???????
        }

        stallDetected = (stableCount >= stableThreshold);
        lastFiltered = filtered;

        return filtered;
    }

    bool isStalled() const {
        return stallDetected;
    }

    void reset() override {
        initialized = false;
        lastFiltered = 0;
        stableCount = 0;
        stallDetected = false;
    }
};

// ================= Low Pass Filter =================
class LowPassFilter : public FilterStrategy {
private:
    float alpha;
    float prev;
    bool initialized = false;
public:
    LowPassFilter(float alpha = 0.1f) : alpha(alpha), prev(0.0f) {}

    float apply(float input) override {
        if (!initialized) {
            prev = input;
            initialized = true;
        }
        prev += alpha * (input - prev);
        return prev;
    }

    void reset() override {
        initialized = false;
        prev = 0;
    }
};

// ================= Median Filter =================
class MedianFilter : public FilterStrategy {
private:
    float buffer[3];
    uint8_t count = 0;
public:
    float apply(float input) override {
        buffer[count++ % 3] = input;
        float a = buffer[0], b = buffer[1], c = buffer[2];

        if (a > b) { float tmp = a; a = b; b = tmp; }
        if (b > c) { float tmp = b; b = c; c = tmp; }
        if (a > b) { float tmp = a; a = b; b = tmp; }

        return b;
    }

    void reset() override {
        buffer[0] = buffer[1] = buffer[2] = 0.0f;
        count = 0;
    }
};

// ================= Derivative Filter =================
class DerivativeFilter : public FilterStrategy {
private:
    float lastValue = 0.0f;
    bool first = true;
public:
    float apply(float input) override {
        if (first) {
            lastValue = input;
            first = false;
            return 0.0f;
        }
        float diff = input - lastValue;
        lastValue = input;
        return diff;
    }

    void reset() override {
        first = true;
        lastValue = 0.0f;
    }
};

// ================= Kalman Filter (Simple) =================
class KalmanFilter : public FilterStrategy {
private:
    float q; // process noise covariance
    float r; // measurement noise covariance
    float x; // value
    float p; // estimation error covariance
    float k; // kalman gain
    bool initialized = false;
public:
    KalmanFilter(float q = 0.125f, float r = 4.0f)
        : q(q), r(r), x(0.0f), p(1.0f), k(0.0f) {}

    float apply(float measurement) override {
        if (!initialized) {
            x = measurement;
            initialized = true;
        }
        p += q;
        k = p / (p + r);
        x += k * (measurement - x);
        p *= (1.0f - k);
        return x;
    }

    void reset() override {
        x = 0;
        p = 1;
        k = 0;
        initialized = false;
    }
};

// =================== Filter Wrapper ===================
class Filter {
public:
    IdentityFilter identity;
    EMAFilter ema;
    LowPassFilter lowpass;
    MedianFilter median;
    DerivativeFilter derivative;
    KalmanFilter kalman;
    StallFilter  stall;
    Filter() {}
};

#endif // FILTER_H
