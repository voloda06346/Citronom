#include "audio_dsp.h"
#include <cstring>
#include <algorithm>

AudioDSP::AudioDSP() : channels(24), output_buffer(1024) {}

void AudioDSP::initialize() {
    for (auto& channel : channels) {
        channel.active = false;
        channel.sample_rate = 32768; // 32 кГц по умолчанию
        channel.volume = 127;
    }
    master_volume = 100;
}

void AudioDSP::write_register(uint32_t addr, uint32_t value) {
    // Эмуляция записи в регистры DSP
    // Адрес определяет параметр (канал, громкость, частота и т. д.)
    switch (addr & 0xFF) {
        case 0x00: // Управление каналами
            for (int i = 0; i < 24; ++i) {
                channels[i].active = (value >> i) & 1;
            }
            break;
        case 0x10: // Мастер‑громкость
            master_volume = value & 0xFF;
            break;
        // Другие регистры...
    }
}

uint32_t AudioDSP::read_register(uint32_t addr) {
    // Чтение состояния DSP
    return 0; // Заглушка
}

void AudioDSP::set_channel_active(int channel_id, bool active) {
    if (channel_id >= 0 && channel_id < 24) {
        channels[channel_id].active = active;
    }
}

void AudioDSP::set_sample_data(int channel_id, int16_t* samples, size_t count) {
    if (channel_id >= 0 && channel_id < 24) {
        auto& channel = channels[channel_id];
        channel.samples = samples;
        channel.sample_count = count;
        channel.current_pos = 0;
    }
}

void AudioDSP::process_audio(int16_t* output, size_t num_samples) {
    std::fill(output_buffer.begin(), output_buffer.end(), 0);

    for (const auto& channel : channels) {
        if (!channel.active || !channel.samples) continue;

        for (size_t i = 0; i < num_samples; ++i) {
            if (channel.current_pos >= channel.sample_count) {
                if (channel.loop_start < channel.loop_end) {
                    channel.current_pos = channel.loop_start;
                } else {
                    break; // Канал завершён
                }
            }

            int32_t sample = channel.samples[channel.current_pos];
            sample = (sample * channel.volume * master_volume) / (127 * 100);
            output_buffer[i] += static_cast<int16_t>(std::clamp(sample, -32768, 32767));
            ++channel.current_pos;
        }
    }

    // Копируем результат в выходной буфер
    std::copy(output_buffer.begin(),
              output_buffer.begin() + std::min(num_samples, output_buffer.size()),
              output);
}
