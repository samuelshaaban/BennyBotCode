#pragma once

enum Bot {A, B};


// modifiable configuration read from file
class Config {
  public:
  Config();
  void read();

  Bot get_bot();

  int get_key_period();
  int get_bat_period();
  int get_control_period();

  double get_min_bat();
  double get_low_bat();

  // more functions to read specific attributes of our config


  private:
  Bot bot;
  // more configuration items read from file
};

/*
for soundboard...:
config needs a way of binding a key sequence / combination to a command number
then command numbers can be bound to filenames

perhaps have controller class store some history:
- keep all analog inputs separate from this, only digital are handled here
- store keys currently being pressed in some sort of struct
- keep a history, maybe 3-4 of the last ones to compute sequences

probably best to think from the xbox controller's perspective, 
for digital inputs we have:
- a,b,x,y
- 4 directions of d-pad
- logo button
- start / whatever the other one is (back?)
- button on each stick
this is 13 different values, could store in a 16-bit map

how to avoid allowing conflicting key binds?:
- perhaps let it happen, just trigger all that apply
- maybe set certain keys as modifiers to designate towards these combinations

maybe set the time steps for history to end whenever a key is released
- avoids history filling with someone entering a combination, instead of each key addition triggering a time step
- user can add on as many keys as they want, and it only registers the combination when they release the first key
- could have the same issue with releasing one at a time, maybe more of a change in concavity detection, 
    * record all keys that were being pressed as soon as one is released
    * then allow them to release as many as they want, but when another is pressed, start the next time step

struct DigitalKeys {
  bool a, b, x, y,
       up, down, left, right,
       start, back, logo,
       left_stick, right_stick;
}; -> probably use a bitmap instead to store in 2 bytes instead of 13

can ignore all keys outside of sequence, rec = recorded, key = values mapped to something, both in same format like DigitalKeys above
if rec & key == key
  then we have pressed at least all necessary keys

can check for as many is needed for sequence
so to store any sequence / combination, just need some list of the minimum keys to press
easier to ignore conflicts and just trigger anything that fits, leaving it to user to deal with preventing any conflicts

*/