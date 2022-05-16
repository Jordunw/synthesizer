use_random_seed 231

C_MAJOR = 0
G_MAJOR = 1
D_MAJOR = 2
A_MAJOR = 3
E_MAJOR = 4
B_MAJOR = 5
Cb_MAJOR = 5
Fs_MAJOR = 6
Gb_MAJOR = 6
Cs_MAJOR = 7
Db_MAJOR = 7
F_MAJOR = 8
Bb_MAJOR = 9
Eb_MAJOR = 10
Ab_MAJOR = 11

A_MINOR = 12
E_MINOR = 13
B_MINOR = 14
Fs_MINOR = 15
Cs_MINOR = 16
Gs_MINOR = 17
Ab_MINOR = 17
Ds_MINOR = 18
Eb_MINOR = 18
As_MINOR = 19
Bb_MINOR = 19
F_MINOR = 20
C_MINOR = 21
D_MINOR = 22

#list of all possible params that i could change. these must be set to default values
#so that they can be applied even when i dont have them wired to a pot/button
#needs to be expanded. see docs for list of all params
#also may need to make these arrays/maps if i want to customize multiple different sounds at the same time
p_chord = false
p_vel_multi = 1.0
p_attack = 0.0
p_attack_level = 1.0
p_decay = 0.0
p_decay_level = 0.0
p_sustain = 1.0
p_sustain_level = 1.0
p_release = 0.0
p_release_level = 1.0
p_pan = 0.0
p_pitch = 0.0
p_env_curve = 2 #shape of curve between envelope levels (attack, decay, etc.) 1=linear 2=exponential 3=sine 4=welch 6=squared 7=cubed
p_slide = 0
p_slide_shape = 5 #shape of curve in a slide 1=linear 3=sine 4=welch 5=custom (see below & pg75 in docs) 6=squared 7=cubed
p_slide_curve = 0 #shape of slide curve (custom) 0=linear, positive=curve up negative=curve down
p_synth_type = 0
p_ksynth_type = 1

pot_range = [0, 127]
# remaps a value to a specific range
# in -> range of the in values (e.g. [0-127])
# out -> range of the out values (e.g. [0-6])
define :remap do |_in, _out, val|
  return ((_out[1] - _out[0]) * (val - _in[0])) / (_in[1] - _in[0]) + _out[0]
end

# 0->toggle 1->enable 2->disable
define :toggle_chords do |mode|
  midi_sysex 0xf0, 1, 0, 0xf7
end

define :set_scale do |scale, octave|
  midi_sysex 0xf0, 0, scale, octave, 0xf7
end

define :get_synth_type do
  case p_synth_type
  when 0
    return :tb303
  when 1
    return :piano
  when 2
    return :dark_ambience
  when 3
    return :prophet
  when 4
    return :dsaw
  when 5
    return :dtri
  when 6
    return :blade
  when 7
    return :kalimba
  when 8
    return :growl
  when 9, 10
    return :saw
  end
end

define :get_keyboard_type do
  if p_ksynth_type == 0
    print "hollow"
    return :hollow
  end
  if p_ksynth_type == 1
    print "piano"
    return :piano
  end
  if p_ksynth_type == 2
    return :dark_ambience
  end
  if p_ksynth_type == 3
    return :prophet
  end
  if p_ksynth_type == 4
    return :dsaw
  end
  if p_ksynth_type == 5
    return :dtri
  end
  if p_ksynth_type == 6
    return :blade
  end
  if p_ksynth_type == 7
    return :dpulse
  end
  if p_ksynth_type == 8
    return :growl
  end
  if p_ksynth_type == 9 || p_ksynth_type == 10
    return :saw
  end
end

define :define_params do |cc, val|
  # sending cc messages 0-5 that i can deal with here
  if cc == 0
    p_attack = (remap pot_range, [0.0, 3.0], val).round(2)
    print "attack: ", p_attack
    return
  end
  if cc == 1
    if val == 63 || val == 64
      p_pan = 0.0
    else
      p_pan = (remap pot_range, [-1.0, 1.0], val).round(2)
    end
    print "pan: ", p_pan
    return
  end
  if cc == 2
    p_sustain = (remap pot_range, [0.0, 3.0], val).round(2)
    print "sustain: ", p_sustain
    return
  end
  if cc == 3
    type_range = [0,10]
    p_ksynth_type = (remap pot_range, type_range, val)
    print "keyboard type: ", get_keyboard_type
    return
  end
  if cc == 4
    p_release = (remap pot_range, [0.0, 3.0], val).round(2)
    print "release: ", p_release
    return
  end
  if cc == 5
    type_range = [0,10]
    p_synth_type = (remap pot_range, type_range, val)
    print "synth type: ", get_synth_type
  end
end



set_scale A_MAJOR, 2
toggle_chords 0

define :play_synth do |note, velocity|
  use_synth get_synth_type
  #with_fx :eq, low_shelf: 1, low_shelf_slope: 0.4 do
  vel = velocity / 100 * p_vel_multi
  play note: note, amp: vel, attack: p_attack, sustain: p_sustain, decay: p_decay, release: p_release, pan: p_pan, pitch: p_pitch
  #if p_chord = true
  #  play note: note + 4, amp: vel, attack: p_attack, sustain: p_sustain, decay: p_decay, release: p_release, pan: p_pan, pitch: p_pitch
  #  play note: note + 7, amp: vel, attack: p_attack, sustain: p_sustain, decay: p_decay, release: p_release, pan: p_pan, pitch: p_pitch
  #  play note: note + 11, amp: vel, attack: p_attack, sustain: p_sustain, decay: p_decay, release: p_release, pan: p_pan, pitch: p_pitch
  #end
  #end
end

define :play_keyboard_synth do |note, velocity|
  #synth_type = get_keyboard_type
  synth_type = :dark_ambient
  use_synth synth_type
  vel = velocity / 80 * p_vel_multi
  
  if synth_type == :piano
    with_fx :reverb, room: 0.5, damp: 0.1 do
      with_fx :echo, amp: 0.25, max_phase: 3, phase: 0.15, mix: 0.9 do
        play note: note, amp: vel * 2, attack: 0.1, sustain: 0.1, decay: 0.5, release: p_release, pan: p_pan, pitch: p_pitch
      end
    end
    return
  end
  
  with_fx :reverb, room: 0.5, damp: 0.2, mix: 0.1 do
    play note: note, amp: vel * 1.25, attack: 1, sustain: 300, release: 5, pan: p_pan, pitch: p_pitch
    #synth :cnoise, amp: 0.02, attack: 5, sustain: 30, release: 5, res: 0.5
  end
  
end

define :play_keyboard do |note, velocity|
  vel = velocity / 80 * p_vel_multi
  sample :ambi_drone, amp: vel
end

in_thread(name: :listener) do
  live_loop :get_cc do
    use_real_time
    #cc, val = sync "/midi:output_1:1/control_change"
    define_params cc, val
  end
end


in_thread(name: :synth_pads) do
  live_loop :synthesizer do
    use_real_time
    cue :tick # sync :tick in other threads to sync to this thread
    #note, velocity = sync "/midi:output_1:2/note_on"
    play_keyboard note, velocity
  end
end

#dont run this until after playing first note

in_thread(name: :white_noise) do
  #live_loop :rand_noise do
  #  with_fx :reverb, room: 0.5, damp: 0.2 do
  #    synth :noise, amp: 0.01, attack: rrand(0.1, 0.2), sustain: rrand(0, 1), release: rrand(0.1, 0.25), pan: rrand(-1, 1)
  #    sleep rrand(0.25, 0.5)
  #end
  #end
end

define getNextKeyboardNote do |count|
  case count
  when 0
    return 60
  end
end

define getNextKeyboardNote do |count|
  case count
    when 0
      return 1
    end

end

in_thread(name: :piano_thread) do
  count = 0
  live_loop :get_keyboard do
    sync :tick
    #note, velocity = sync "/midi:digital_keyboard_0:1/note_on"
    
  end
end
