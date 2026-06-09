CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
TARGET   = recommend
SRCDIR   = src
OBJDIR   = obj

OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/Movie.o \
       $(OBJDIR)/User.o \
       $(OBJDIR)/Rating.o \
       $(OBJDIR)/MovieManager.o \
       $(OBJDIR)/UserManager.o \
       $(OBJDIR)/RatingManager.o \
       $(OBJDIR)/SimilarityCalculator.o \
       $(OBJDIR)/Recommender.o \
       $(OBJDIR)/Statistics.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

makecsv: $(SRCDIR)/makecsv.cpp
	$(CXX) $(CXXFLAGS) -o makecsv $(SRCDIR)/makecsv.cpp

run: makecsv $(TARGET)
	@[ -f data/ratings.csv ] || ./makecsv
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET) makecsv

.PHONY: all run clean