# CMPSC122-Final_Project-Godfather_Airport
Set up an airport for Don Vito - and decide who lives and who dies.

My Godfather (the Don, Michael Corleone) is the head of a major
corporation that deals with olive oil imports from Sicily, legalized personal
companionship, distilleries, and legal casinos gambling
• His corporation (families) interest span the United States from N.Y. N.J.
Chicago, and Kansas City to name a few.
• Because the Don is a “Family” man and wants to personally talk with the
CEOs of his interests together (and separately- when need be ). For security
reasons he has decided to build an airport that will accommodate both
commercial and business travel

Actual Specifictions:
- Build an air traffic control system
- 2 runways are available. 
- Planes should be able to take off and land.
- Planes contain: fuel, cost of cargo, # of passengers, if a family member is on board
- Will be able to tell if there are family members on board a plane coming in to land.
- Planes must have 20 units of fuel to take off (otherwise sent back to gate). Refueling takes 10 units of time.
- Runway can help a plane land or take off at any given time unit.

Input specifications:
- Commands
  - D: Data, followed by actual data
  - P: Print given data
  - W: Wait for carriage return
- Time - integer
- Actions
  - A: Arrival
  - D: Departure
- Fuel - integer
- People - integer
- Cargo - float
- Special - character (Y or N depending on whether there is a 'grandchild' on board)

Stats to keep in mind:
• Your program should process the input file and perform the requested action.
• You should keep the following statistics, and display after the file has been
processed or on command:
  • Average Take off wait time
  • Average landing wait time
  • Number of plan crash
  • Number of plans departing
  • Number of planes arriving
  • Number of people that landed safely
  • Number of people killed
  • Number of Grandchildren killed
  • Average wait time for a grandchild Arriving or departing. (Dead grandchildren not included)
  • Amount of cargo that landed safely
  • Amount of destroyed Cargo
  • Amount of time it takes to process a input file
