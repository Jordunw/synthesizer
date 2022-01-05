from abc import ABC, abstractmethod
import math

notes = {}
# Note     [Freq (Hz), Wavelength(cm)]
notes["C0"]  = [16.35, 2109.89]
notes["C#0"] = [17.32, 1991.47]
notes["D0"]  = [18.35, 1879.69]
notes["D#0"] = [19.45, 1774.2]
notes["E0"]  = [20.60, 1674.62]
notes["F0"]  = [21.83, 1580.63]
notes["F#0"] = [23.12, 1491.91]
notes["G0"]  = [24.5, 1408.18]
notes["G#0"] = [25.96, 1329.14]
notes["A0"]  = [27.5, 1254.55]
notes["A#0"] = [29.14, 1184.13]
notes["B0"]  = [30.87, 1117.67]

notes["C1"]  = [32.7, 1054.94]
notes["C#1"] = [34.65, 995.73]
notes["D1"]  = [36.71, 939.85]
notes["D#1"] = [38.89, 887.1]
notes["E1"]  = [41.2, 837.31]
notes["F1"]  = [43.65, 790.31]
notes["F#1"] = [46.25, 745.96]
notes["G1"]  = [49.0, 704.09]
notes["G#1"] = [51.91, 664.57]
notes["A1"]  = [55.0, 627.27]
notes["A#1"] = [58.27, 592.07]
notes["B1"]  = [61.74, 558.84]

notes["C2"]  = [65.41, 527.47]
notes["C#2"] = [69.3, 497.87]
notes["D2"]  = [73.42, 469.92]
notes["D#2"] = [77.78, 443.55]
notes["E2"]  = [82.41, 418.65]
notes["F2"]  = [87.31, 395.16]
notes["F#2"] = [92.5, 372.98]
notes["G2"]  = [98.0, 352.04]
notes["G#2"] = [103.83, 332.29]
notes["A2"]  = [110.0, 313.64]
notes["A#2"] = [116.54, 296.03]
notes["B2"]  = [123.47, 279.42]

notes["C3"]  = [130.81, 263.74]
notes["C#3"] = [138.59, 248.93]
notes["D3"]  = [146.83, 234.96]
notes["D#3"] = [155.56, 221.77]
notes["E3"]  = [164.81, 209.33]
notes["F3"]  = [174.61, 197.58]
notes["F#3"] = [185.0, 186.49]
notes["G3"]  = [196.0, 176.02]
notes["G#3"] = [207.65, 166.14]
notes["A3"]  = [220.0, 156.82]
notes["A#3"] = [233.08, 148.02]
notes["B3"]  = [246.94, 139.71]

notes["C4"]  = [261.63, 131.87]
notes["C#4"] = [277.18, 124.47]
notes["D4"]  = [293.66, 117.48]
notes["D#4"] = [311.13, 110.89]
notes["E4"]  = [329.63, 104.66]
notes["F4"]  = [349.23, 98.79]
notes["F#4"] = [369.99, 93.24]
notes["G4"]  = [392.0, 88.01]
notes["G#4"] = [415.3, 83.07]
notes["A4"]  = [440.0, 78.41]
notes["A#4"] = [466.16, 74.01]
notes["B4"]  = [493.88, 69.85]

notes["C5"]  = [523.25, 65.93]
notes["C#5"] = [554.37, 62.23]
notes["D5"]  = [587.33, 58.74]
notes["D#5"] = [622.25, 55.44]
notes["E5"]  = [659.25, 52.33]
notes["F5"]  = [698.46, 49.39]
notes["F#5"] = [739.99, 46.62]
notes["G5"]  = [783.99, 44.01]
notes["G#5"] = [830.61, 41.54]
notes["A5"]  = [880.0, 39.2]
notes["A#5"] = [932.33, 37.00]
notes["B5"]  = [987.77, 34.93]

notes["C6"]  = [1046.5, 32.97]
notes["C#6"] = [1108.73, 31.12]
notes["D6"]  = [1174.66, 29.37]
notes["D#6"] = [1244.51, 27.72]
notes["E6"]  = [1318.51, 26.17]
notes["F6"]  = [1396.91, 24.7]
notes["F#6"] = [1479.98, 23.31]
notes["G6"]  = [1567.98, 22.0]
notes["G#6"] = [1661.22, 20.77]
notes["A6"]  = [1760.0, 19.6]
notes["A#6"] = [1864.66, 18.5]
notes["B6"]  = [1975.53, 17.46]

notes["C7"]  = [2093.0, 16.48]
notes["C#7"] = [2217.46, 15.56]
notes["D7"]  = [2349.32, 14.69]
notes["D#7"] = [2489.02, 13.86]
notes["E7"]  = [2637.02, 13.08]
notes["F7"]  = [2793.83, 12.35]
notes["F#7"] = [2959.96, 11.66]
notes["G7"]  = [3136.96, 11.0]
notes["G#7"] = [3322.44, 10.38]
notes["A7"]  = [3520.0, 9.80]
notes["A#7"] = [3729.31, 9.25]
notes["B7"]  = [3951.07, 8.73]

notes["C8"]  = [4186.01, 8.24]
notes["C#8"] = [4434.92, 7.78]
notes["D8"]  = [4698.63, 7.34]
notes["D#8"] = [4978.03, 6.93]
notes["E8"]  = [5274.04, 6.54]
notes["F8"]  = [5587.65, 6.17]
notes["F#8"] = [5919.91, 5.83]
notes["G8"]  = [6271.93, 5.5]
notes["G#8"] = [6644.88, 5.19]
notes["A8"]  = [7040.0, 4.9]
notes["A#8"] = [7458.62, 4.63]
notes["B8"]  = [7902.13, 4.37]

class Oscillator(ABC):
    def __init__(self, freq=440, phase=0, amp=1, \
                 sample_rate=192000, wave_range=(-1,1)):
        self._freq = freq
        self._amp = amp
        self._phase = phase
        self._sample_rate = sample_rate
        self._wave_range = wave_range

        self._f = freq
        self._a = amp
        self._p = phase

    @property
    def init_freq(self):
        return self._freq

    @property
    def init_amp(self):
        return self._amp
    
    @property
    def init_phase(self):
        return self._phase

    @property
    def freq(self):
        return self._f

    @freq.setter
    def freq(self, value):
        self._f = value
        self._post_freq_set()

    @property
    def amp(self):
        return self._a

    @amp.setter
    def amp(self, value):
        self._a = value
        self._post_amp_set()

    @property
    def phase(self):
        return self._p

    @phase.setter
    def phase(self, value):
        self._p = value
        self._post_phase_set()

    def _post_freq_set(self):
        pass 
    
    def _post_amp_set(self):
        pass

    def _post_phase_set(self):
        pass

    @abstractmethod
    def _initialize_osc(self):
        pass
    
    @staticmethod
    def squish_val(val, min_val=0, max_val=1):
        return (((val + 1) / 2) * (max_val - min_val)) + min_val

    @abstractmethod
    def __next__(self):
        return None

    def __iter__(self):
        self.freq = self._freq
        self.phase = self._phase
        self.amp = self._amp
        self._initialize_osc()
        return self


class SineOscillator(Oscillator):
    def _post_freq_set(self):
        self._step = (2 * math.pi * self._f) / self._sample_rate

    def _post_phase_set(self):
        self._p = (self._p / 360) * 2 * math.pi
    
    def _initialize_osc(self):
        self._i = 0

    def __next__(self):
        val = math.sin(self._i + self._p)
        self._i += self._step
        if self._wave_range != (-1, 1):
            val = self.squish_val(val, *self._wave_range)
        return val * self._a

class SquareOscillator(SineOscillator):
    def __init__(self, freq=440, phase=0, amp=1, \
                 sample_rate=192000, wave_range=(-1,1), threshold=0):
        super().__init__(freq, phase, amp, sample_rate, wave_range)
        self.threshold = threshold

    def __next__(self):
        val = math.sin(self._i + self._p)
        self._i = self._i + self._step
        if val < self.threshold:
            val = self._wave_range[0]
        else:
            val = self._wave_range[1]
        return val * self._a

class SawtoothOscillator(Oscillator):
    def _post_freq_set(self):
        self._period = self._sample_rate / self._f
        self._post_phase_set
        
    def _post_phase_set(self):
        self._p = ((self._p + 90)/ 360) * self._period
    
    def _initialize_osc(self):
        self._i = 0
    
    def __next__(self):
        div = (self._i + self._p )/self._period
        val = 2 * (div - math.floor(0.5 + div))
        self._i = self._i + 1
        if self._wave_range != (-1, 1):
            val = self.squish_val(val, *self._wave_range)
        return val * self._a

class TriangleOscillator(SawtoothOscillator):
    def __next__(self):
        div = (self._i + self._p)/self._period
        val = 2 * (div - math.floor(0.5 + div))
        val = (abs(val) - 0.5) * 2
        self._i = self._i + 1
        if self._wave_range != (-1, 1):
            val = self.squish_val(val, *self._wave_range)
        return val * self._a

class WaveAdder:
    def __init__(self, *oscillators):
        self.oscillators = oscillators
        self.n = len(oscillators)

    def __iter__(self):
        [iter(osc) for osc in self.oscillators]
        return self
    
    def __next__(self):
        return sum(next(osc) for osc in self.oscillators) / self.n

import numpy as np
from scipy.io import wavfile

def wave_to_file(wav, wav2=None, fname="temp.wav", amp=0.1, sample_rate=192000):
    wav = np.array(wav)
    wav = np.int16(wav * amp * (2**15 - 1))
    
    if wav2 is not None:
        wav2 = np.array(wav2)
        wav2 = np.int16(wav2 * amp * (2 ** 15 - 1))
        wav = np.stack([wav, wav2]).T
    
    wavfile.write(fname, sample_rate, wav)

gen = WaveAdder(
    SineOscillator(freq=notes["G4"][0]),
    TriangleOscillator(freq=notes["B4"][0]),
    SawtoothOscillator(freq=notes["D4"][0]),
    SquareOscillator(freq=notes["G4"][0]),
)
iter(gen)
wav = [next(gen) for _ in range(192000 * 4)] # 4 Seconds
wave_to_file(wav, fname="test3.wav")