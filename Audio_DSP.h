#pragma once
#include <cstdint>
#include <vector>
#include <memory>

class AudioDSP {
private:
    struct Channel {
        bool active = false;
        uint32_t sample_rate = 0;
        uint32_t loop_start = 0;
        uint32_t loop_end = 0;
        uint8_t volume = 0;
        int16_t* samples = nullptr;
        size_t sample_count = 0;
        size_t current_pos = 0;
    };

    std::vector<Channel> channels;
    std::vector<int16_t> output_buffer;
    uint32_t master_volume = 100;

public:
    AudioDSP();
    void initialize();
    void write_register(uint32_t addr, uint32_t value);
    uint32_t read_register(uint32_t addr);
    void process_audio(int16_t* output, size_t num_samples);
    void set_channel_active(int channel_id, bool active);
    void set_sample_data(int channel_id, int16_t* samples, size_t count);
};
