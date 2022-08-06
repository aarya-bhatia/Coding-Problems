#include <string.h>
#include <assert.h>
#include <vector>
#include <list>
#include <stdio.h>

struct Time {
    int hours;
    int minutes;

    Time(const char *timeString)
    {
        hours = 0;
        minutes = 0;
        sscanf(timeString, "%d:%d", &hours, &minutes);
    }

    bool operator<(const Time &other) const
    {
        if(hours == other.hours)
        {
            return minutes < other.minutes;
        }

        return hours < other.hours;
    }

    bool operator==(const Time &other) const
    {
        return hours == other.hours && minutes == other.minutes;
    }

    bool isBetween(const Time &start, const Time &end) const
    {
        return (start < *this || start == *this) && 
            (*this < end || *this == end);
    }
};

struct TimeRange
{
    Time startTime;
    Time endTime;

    TimeRange(Time start, Time end): startTime(start), endTime(end)
    {
    }

    bool operator<(const TimeRange &other) const
    {
        return startTime < other.startTime && endTime < other.endTime;
    }

    bool operator=(const TimeRange &other) const
    {
        return startTime == other.startTime && endTime == other.endTime;
    }

    bool overlaps(TimeRange other) const
    {
        return startTime.isBetween(other.startTime, other.endTime) ||
            other.startTime.isBetween(startTime, endTime);
    }

    TimeRange merge(TimeRange other) const
    {
        Time newStartTime = std::min(startTime, other.startTime);
        Time newEndTime = std::max(endTime, other.endTime);
        return TimeRange(newStartTime, newEndTime);
    }

    int getDurationInMinutes() const
    {
        int deltaHours = endTime.hours - startTime.hours;
        int deltaMinutes = endTime.minutes - startTime.minutes;
        return deltaMinutes + (deltaHours * 60);
    }
};

std::list<TimeRange> *scheduleMeeting(std::vector<TimeRange> cal1, std::vector<TimeRange> cal2, TimeRange bounds, int durationInMinutes)
{
    std::list<TimeRange> *freeTime = new std::list<TimeRange>();

    if(cal1.empty() && cal2.empty())
    {
        freeTime->push_back(bounds);
        return freeTime;
    }

    std::list<TimeRange> used; 

    auto i = cal1.begin();
    auto j = cal2.begin();

    while(i != cal1.end() && j != cal2.end())
    {
        TimeRange t1 = *i;
        TimeRange t2 = *j;

        if(t1.overlaps(t2))
        {
            TimeRange t = t1.merge(t2);
            used.push_back(t);
            i++; 
            j++;
        }
        else if(t1 < t2)
        {
            used.push_back(t1);
            i++;
        }
        else
        {
            used.push_back(t2);
            j++;
        }
    }

    while(i != cal1.end())
    {
        used.push_back(*i++);
    }

    while(j != cal2.end())
    {
        used.push_back(*j++);
    }

    // Get available time slots from used time list

    auto usedItr = used.begin();

    auto nextItr = used.begin();
    nextItr++;

    while(nextItr != used.end())
    {
        TimeRange freeSlot(usedItr->endTime, nextItr->startTime);
        
        if(freeSlot.getDurationInMinutes() >= durationInMinutes)
        {
            freeTime->push_back(freeSlot);
        }

        usedItr++;
        nextItr++;
    }

    printf("Used Times:");

    for(TimeRange tr: used)
    {
        printf("[%02d:%02d, %02d:%02d] ", tr.startTime.hours, tr.startTime.minutes, tr.endTime.hours, tr.endTime.minutes);
    }

    printf("\n");

    // Edge case times

    if(bounds.startTime < used.front().startTime)
    {
        TimeRange slot(bounds.startTime, used.front().startTime);
        if(slot.getDurationInMinutes() >= durationInMinutes) freeTime->push_front(slot);
    }

    if(used.back().endTime < bounds.endTime)
    {
        TimeRange slot(used.back().endTime, bounds.endTime);
        if(slot.getDurationInMinutes() >= durationInMinutes) freeTime->push_back(slot);
    }

    return freeTime;
}

int main()
{
    std::vector<TimeRange> cal1;
    std::vector<TimeRange> cal2;

    cal1.push_back(TimeRange(Time("10:05"), Time("10:15")));
    cal1.push_back(TimeRange(Time("11:00"), Time("11:25")));
    cal1.push_back(TimeRange(Time("12:00"), Time("13:00")));
    cal1.push_back(TimeRange(Time("15:00"), Time("16:00")));
    
    cal2.push_back(TimeRange(Time("10:30"), Time("11:30")));
    cal2.push_back(TimeRange(Time("12:10"), Time("12:40")));
    cal2.push_back(TimeRange(Time("13:55"), Time("14:15")));
    cal2.push_back(TimeRange(Time("16:35"), Time("17:00")));

    TimeRange bounds(Time("9:30"), Time("17:00"));

    int durationMin = 15;

    std::list<TimeRange> *result = scheduleMeeting(cal1, cal2, bounds, durationMin);

    for(TimeRange tr: *result)
    {
        printf("[%02d:%02d, %02d:%02d] ", tr.startTime.hours, tr.startTime.minutes, tr.endTime.hours, tr.endTime.minutes);
    }

    delete result;

    return 0;
}
