/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SupportMgr_h__
#define SupportMgr_h__

#include "ObjectMgr.h"
#include "Player.h"
#include "TicketPackets.h"

class ChatHandler;

// from blizzard lua
enum GMTicketSystemStatus
{
    GMTICKET_QUEUE_STATUS_DISABLED  = 0,
    GMTICKET_QUEUE_STATUS_ENABLED   = 1
};

enum GMSupportComplaintType
{
    GMTICKET_SUPPORT_COMPLAINT_TYPE_NONE        = 0,
    GMTICKET_SUPPORT_COMPLAINT_TYPE_LANGUAGE    = 2,
    GMTICKET_SUPPORT_COMPLAINT_TYPE_PLAYERNAME  = 4,
    GMTICKET_SUPPORT_COMPLAINT_TYPE_CHEAT       = 15,
    GMTICKET_SUPPORT_COMPLAINT_TYPE_GUILDNAME   = 23,
    GMTICKET_SUPPORT_COMPLAINT_TYPE_SPAMMING    = 24
};

using ChatLog = WorldPackets::Ticket::SupportTicketSubmitComplaint::SupportTicketChatLog;

class Ticket
{
public:
    Ticket();
    Ticket(Player* player);
    virtual ~Ticket();

    bool IsClosed() const { return !_closedBy.IsEmpty(); }
    bool IsFromPlayer(ObjectGuid guid) const { return guid == _playerGuid; }
    bool IsAssigned() const { return !_assignedTo.IsEmpty(); }
    bool IsAssignedTo(ObjectGuid guid) const { return guid == _assignedTo; }
    bool IsAssignedNotTo(ObjectGuid guid) const { return IsAssigned() && !IsAssignedTo(guid); }

    uint32 GetId() const { return _id; }
    ObjectGuid GetPlayerGuid() const { return _playerGuid; }
    Player* GetPlayer() const { return ObjectAccessor::FindConnectedPlayer(_playerGuid); }
    std::string GetPlayerName() const
    {
        std::string name;
        if (!_playerGuid.IsEmpty())
            ObjectMgr::GetPlayerNameByGUID(_playerGuid, name);

        return name;
    }
    Player* GetAssignedPlayer() const { return ObjectAccessor::FindConnectedPlayer(_assignedTo); }
    ObjectGuid GetAssignedToGUID() const { return _assignedTo; }
    std::string GetAssignedToName() const
    {
        std::string name;
        if (!_assignedTo.IsEmpty())
            ObjectMgr::GetPlayerNameByGUID(_assignedTo, name);

        return name;
    }
    std::string const& GetComment() { return _comment; }

    virtual void SetAssignedTo(ObjectGuid guid, bool /*isAdmin*/ = false) { _assignedTo = guid; }
    virtual void SetUnassigned() { _assignedTo.Clear(); }
    void SetClosedBy(ObjectGuid value) { _closedBy = value; }
    void SetComment(std::string const& comment) { _comment = comment; }
    void SetPosition(uint32 mapId, G3D::Vector3& pos)
    {
        _mapId = mapId;
        _pos = pos;
    }

    virtual void LoadFromDB(Field* fields) = 0;
    virtual void SaveToDB() const = 0;
    virtual void DeleteFromDB() = 0;

    void TeleportTo(Player* player) const;

    virtual std::string FormatViewMessageString(ChatHandler& handler, bool detailed = false) const = 0;
    virtual std::string FormatViewMessageString(ChatHandler& handler, const char* szClosedName, const char* szAssignedToName, const char* szUnassignedName, const char* szDeletedName) const;

protected:
    uint32 _id;
    ObjectGuid _playerGuid;
    uint16 _mapId;
    G3D::Vector3 _pos;
    uint64 _createTime;
    ObjectGuid _closedBy; // 0 = Open, -1 = Console, playerGuid = player abandoned ticket, other = GM who closed it.
    ObjectGuid _assignedTo;
    std::string _comment;
};

class BugTicket : public Ticket
{
public:
    BugTicket();
    BugTicket(Player* player);
    ~BugTicket();

    std::string const& GetNote() const { return _note; }

    void SetFacing(float facing) { _facing = facing; }
    void SetNote(std::string const& note) { _note = note; }

    void LoadFromDB(Field* fields) override;
    void SaveToDB() const override;
    void DeleteFromDB() override;

    using Ticket::FormatViewMessageString;
    std::string FormatViewMessageString(ChatHandler& handler, bool detailed = false) const override;

private:
    float _facing;
    std::string _note;
};

class ComplaintTicket : public Ticket
{
public:
    ComplaintTicket();
    ComplaintTicket(Player* player);
    ~ComplaintTicket();

    ObjectGuid GetTargetCharacterGuid() const { return _targetCharacterGuid; }
    GMSupportComplaintType GetComplaintType() const { return _complaintType; }
    std::string const& GetNote() const { return _note; }

    void SetFacing(float facing) { _facing = facing; }
    void SetTargetCharacterGuid(ObjectGuid targetCharacterGuid)
    {
        _targetCharacterGuid = targetCharacterGuid;
    }
    void SetComplaintType(GMSupportComplaintType type) { _complaintType = type; }
    void SetChatLog(ChatLog const& log) { _chatLog = log; }
    void SetNote(std::string const& note) { _note = note; }

    void LoadFromDB(Field* fields) override;
    void LoadChatLineFromDB(Field* fields);
    void SaveToDB() const override;
    void DeleteFromDB() override;

    using Ticket::FormatViewMessageString;
    std::string FormatViewMessageString(ChatHandler& handler, bool detailed = false) const override;

private:
    float _facing;
    ObjectGuid _targetCharacterGuid;
    GMSupportComplaintType _complaintType;
    ChatLog _chatLog;
    std::string _note;
};

class SuggestionTicket : public Ticket
{
public:
    SuggestionTicket();
    SuggestionTicket(Player* player);
    ~SuggestionTicket();

    std::string const& GetNote() const { return _note; }
    void SetNote(std::string const& note) { _note = note; }

    void SetFacing(float facing) { _facing = facing; }

    void LoadFromDB(Field* fields) override;
    void SaveToDB() const override;
    void DeleteFromDB() override;

    using Ticket::FormatViewMessageString;
    std::string FormatViewMessageString(ChatHandler& handler, bool detailed = false) const override;

private:
    float _facing;
    std::string _note;
};

typedef std::map<uint32, BugTicket*> BugTicketList;
typedef std::map<uint32, ComplaintTicket*> ComplaintTicketList;
typedef std::map<uint32, SuggestionTicket*> SuggestionTicketList;

class SupportMgr
{
private:
    SupportMgr();
    ~SupportMgr();

public:
    static SupportMgr* instance()
    {
        static SupportMgr instance;
        return &instance;
    }

    template<typename T>
    T* GetTicket(uint32 ticketId);

    ComplaintTicketList GetComplaintsByPlayerGuid(ObjectGuid playerGuid) const
    {
        ComplaintTicketList ret;
        for (auto const& c : _complaintTicketList)
            if (c.second->GetPlayerGuid() == playerGuid)
                ret.insert(c);

        return ret;
    }

    void Initialize();

    bool GetSupportSystemStatus() { return _supportSystemStatus; }
    bool GetTicketSystemStatus() { return _supportSystemStatus && _ticketSystemStatus; }
    bool GetBugSystemStatus() { return _supportSystemStatus && _bugSystemStatus; }
    bool GetComplaintSystemStatus() { return _supportSystemStatus && _complaintSystemStatus; }
    bool GetSuggestionSystemStatus() { return _supportSystemStatus && _suggestionSystemStatus; }
    uint64 GetLastChange() const { return _lastChange; }
    template<typename T>
    uint32 GetOpenTicketCount() const;

    void SetSupportSystemStatus(bool status) { _supportSystemStatus = status; }
    void SetTicketSystemStatus(bool status) { _ticketSystemStatus = status; }
    void SetBugSystemStatus(bool status) { _bugSystemStatus = status; }
    void SetComplaintSystemStatus(bool status) { _complaintSystemStatus = status; }
    void SetSuggestionSystemStatus(bool status) { _suggestionSystemStatus = status; }

    void LoadBugTickets();
    void LoadComplaintTickets();
    void LoadSuggestionTickets();

    void AddTicket(BugTicket* ticket);
    void AddTicket(ComplaintTicket* ticket);
    void AddTicket(SuggestionTicket* ticket);

    template<typename T>
    void RemoveTicket(uint32 ticketId);

    template<typename T>
    void CloseTicket(uint32 ticketId, ObjectGuid closedBy);

    template<typename T>
    void ResetTickets();

    template<typename T>
    void ShowList(ChatHandler& handler) const;

    template<typename T>
    void ShowList(ChatHandler& handler, bool onlineOnly) const;

    template<typename T>
    void ShowClosedList(ChatHandler& handler) const;

    void UpdateLastChange() { _lastChange = uint64(time(nullptr)); }

    uint32 GenerateBugId() { return ++_lastBugId; }
    uint32 GenerateComplaintId() { return ++_lastComplaintId; }
    uint32 GenerateSuggestionId() { return ++_lastSuggestionId; }

private:
    bool _supportSystemStatus;
    bool _ticketSystemStatus;
    bool _bugSystemStatus;
    bool _complaintSystemStatus;
    bool _suggestionSystemStatus;
    BugTicketList _bugTicketList;
    ComplaintTicketList _complaintTicketList;
    SuggestionTicketList _suggestionTicketList;
    uint32 _lastBugId;
    uint32 _lastComplaintId;
    uint32 _lastSuggestionId;
    uint64 _lastChange;
    uint32 _openBugTicketCount;
    uint32 _openComplaintTicketCount;
    uint32 _openSuggestionTicketCount;
};

#define sSupportMgr SupportMgr::instance()

#endif // SupportMgr_h__
