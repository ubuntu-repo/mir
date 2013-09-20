/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Thomas Guest <thomas.guest@canonical.com>
 */

#ifndef MIR_FRONTEND_PROTOBUF_ASIO_COMMUNICATOR_H_
#define MIR_FRONTEND_PROTOBUF_ASIO_COMMUNICATOR_H_

#include "connected_sessions.h"

#include "mir/frontend/communicator.h"
#include "mir/frontend/socket_connection.h"

#include <boost/asio.hpp>

#include <atomic>
#include <thread>
#include <string>
#include <vector>
#include <functional>

namespace google
{
namespace protobuf
{
class Message;
}
}

namespace mir
{
namespace frontend
{
class ResourceCache;
class ProtobufIpcFactory;
class SessionAuthorizer;

namespace detail
{
struct SocketSession;
class MessageSender;
}

class CommunicatorReport;

// Temporary class to hoist functionality apart
class SessionCreator
{
public:
    explicit SessionCreator(
        std::shared_ptr<ProtobufIpcFactory> const& ipc_factory,
        std::shared_ptr<SessionAuthorizer> const& session_authorizer);
    ~SessionCreator() noexcept;
    void create_session_for(std::shared_ptr<boost::asio::local::stream_protocol::socket> const& socket);

private:
    int next_id();

    std::shared_ptr<ProtobufIpcFactory> const ipc_factory;
    std::shared_ptr<SessionAuthorizer> const session_authorizer;
    std::atomic<int> next_session_id;
    std::shared_ptr<detail::ConnectedSessions<detail::SocketSession>> const connected_sessions;
};


class ProtobufSocketCommunicator : public Communicator
{
public:
    // Create communicator based on Boost asio and Google protobufs
    // using the supplied socket.
    explicit ProtobufSocketCommunicator(
        std::shared_ptr<SocketConnection> const& socket_connection,
        std::shared_ptr<ProtobufIpcFactory> const& ipc_factory,
        std::shared_ptr<SessionAuthorizer> const& session_authorizer,
        int threads,
        std::function<void()> const& force_requests_to_complete,
        std::shared_ptr<CommunicatorReport> const& report);
    ~ProtobufSocketCommunicator() noexcept;
    void start() override;
    void stop() override;

private:
    void start_accept();
    void on_new_connection(std::shared_ptr<boost::asio::local::stream_protocol::socket> const& socket,
                           boost::system::error_code const& ec);

    std::shared_ptr<SocketConnection> const socket_connection;
    boost::asio::io_service io_service;
    boost::asio::local::stream_protocol::acceptor acceptor;
    std::vector<std::thread> io_service_threads;
    std::function<void()> const force_requests_to_complete;
    std::shared_ptr<CommunicatorReport> const report;
    SessionCreator impl;
};

}
}

#endif // MIR_FRONTEND_PROTOBUF_ASIO_COMMUNICATOR_H_
