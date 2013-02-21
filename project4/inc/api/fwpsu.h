/*
   Copyright (c) Microsoft Corporation

   SYNOPSIS

     Declares the system portion of the FWP API.
*/

#ifndef FWPSX_H
#define FWPSX_H
#if _MSC_VER >= 1020
#pragma once
#endif

#include "fwpstypes.h"
#include "ws2def.h"

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
//
// LUIDs for built-in layers.
//
///////////////////////////////////////////////////////////////////////////////

typedef enum FWPS_BUILTIN_LAYERS_
{
   // Kernel-mode layers
   FWPS_LAYER_INBOUND_IPPACKET_V4,
   FWPS_LAYER_INBOUND_IPPACKET_V4_DISCARD,
   FWPS_LAYER_INBOUND_IPPACKET_V6,
   FWPS_LAYER_INBOUND_IPPACKET_V6_DISCARD,
   FWPS_LAYER_OUTBOUND_IPPACKET_V4,
   FWPS_LAYER_OUTBOUND_IPPACKET_V4_DISCARD,
   FWPS_LAYER_OUTBOUND_IPPACKET_V6,
   FWPS_LAYER_OUTBOUND_IPPACKET_V6_DISCARD,
   FWPS_LAYER_IPFORWARD_V4,
   FWPS_LAYER_IPFORWARD_V4_DISCARD,
   FWPS_LAYER_IPFORWARD_V6,
   FWPS_LAYER_IPFORWARD_V6_DISCARD,
   FWPS_LAYER_INBOUND_TRANSPORT_V4,
   FWPS_LAYER_INBOUND_TRANSPORT_V4_DISCARD,
   FWPS_LAYER_INBOUND_TRANSPORT_V6,
   FWPS_LAYER_INBOUND_TRANSPORT_V6_DISCARD,
   FWPS_LAYER_OUTBOUND_TRANSPORT_V4,
   FWPS_LAYER_OUTBOUND_TRANSPORT_V4_DISCARD,
   FWPS_LAYER_OUTBOUND_TRANSPORT_V6,
   FWPS_LAYER_OUTBOUND_TRANSPORT_V6_DISCARD,
   FWPS_LAYER_STREAM_V4,
   FWPS_LAYER_STREAM_V4_DISCARD,
   FWPS_LAYER_STREAM_V6,
   FWPS_LAYER_STREAM_V6_DISCARD,
   FWPS_LAYER_DATAGRAM_DATA_V4,
   FWPS_LAYER_DATAGRAM_DATA_V4_DISCARD,
   FWPS_LAYER_DATAGRAM_DATA_V6,
   FWPS_LAYER_DATAGRAM_DATA_V6_DISCARD,
   FWPS_LAYER_INBOUND_ICMP_ERROR_V4,
   FWPS_LAYER_INBOUND_ICMP_ERROR_V4_DISCARD,
   FWPS_LAYER_INBOUND_ICMP_ERROR_V6,
   FWPS_LAYER_INBOUND_ICMP_ERROR_V6_DISCARD,
   FWPS_LAYER_OUTBOUND_ICMP_ERROR_V4,
   FWPS_LAYER_OUTBOUND_ICMP_ERROR_V4_DISCARD,
   FWPS_LAYER_OUTBOUND_ICMP_ERROR_V6,
   FWPS_LAYER_OUTBOUND_ICMP_ERROR_V6_DISCARD,
   FWPS_LAYER_ALE_RESOURCE_ASSIGNMENT_V4,
   FWPS_LAYER_ALE_RESOURCE_ASSIGNMENT_V4_DISCARD,
   FWPS_LAYER_ALE_RESOURCE_ASSIGNMENT_V6,
   FWPS_LAYER_ALE_RESOURCE_ASSIGNMENT_V6_DISCARD,
   FWPS_LAYER_ALE_AUTH_LISTEN_V4,
   FWPS_LAYER_ALE_AUTH_LISTEN_V4_DISCARD,
   FWPS_LAYER_ALE_AUTH_LISTEN_V6,
   FWPS_LAYER_ALE_AUTH_LISTEN_V6_DISCARD,
   FWPS_LAYER_ALE_AUTH_RECV_ACCEPT_V4,
   FWPS_LAYER_ALE_AUTH_RECV_ACCEPT_V4_DISCARD,
   FWPS_LAYER_ALE_AUTH_RECV_ACCEPT_V6,
   FWPS_LAYER_ALE_AUTH_RECV_ACCEPT_V6_DISCARD,
   FWPS_LAYER_ALE_AUTH_CONNECT_V4,
   FWPS_LAYER_ALE_AUTH_CONNECT_V4_DISCARD,
   FWPS_LAYER_ALE_AUTH_CONNECT_V6,
   FWPS_LAYER_ALE_AUTH_CONNECT_V6_DISCARD,
   FWPS_LAYER_ALE_FLOW_ESTABLISHED_V4,
   FWPS_LAYER_ALE_FLOW_ESTABLISHED_V4_DISCARD,
   FWPS_LAYER_ALE_FLOW_ESTABLISHED_V6,
   FWPS_LAYER_ALE_FLOW_ESTABLISHED_V6_DISCARD,

   // User-mode layers
   FWPS_LAYER_IPSEC_KM_DEMUX_V4,
   FWPS_LAYER_IPSEC_KM_DEMUX_V6,
   FWPS_LAYER_IPSEC_V4,
   FWPS_LAYER_IPSEC_V6,
   FWPS_LAYER_IKEEXT_V4,
   FWPS_LAYER_IKEEXT_V6,
   FWPS_LAYER_RPC_UM,
   FWPS_LAYER_RPC_EPMAP,
   FWPS_LAYER_RPC_EP_ADD,
   FWPS_LAYER_RPC_PROXY_CONN,
   FWPS_LAYER_RPC_PROXY_IF,
   FWPS_BUILTIN_LAYER_MAX
} FWPS_BUILTIN_LAYERS;

#define FWPS_BUILTIN_KM_LAYER_MAX FWPS_LAYER_IPSEC_KM_DEMUX_V4

///////////////////////////////////////////////////////////////////////////////
//
// LUIDs for built-in fields.
//
///////////////////////////////////////////////////////////////////////////////

typedef enum FWPS_FIELDS_INBOUND_IPPACKET_V4_
{
   FWPS_FIELD_INBOUND_IPPACKET_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_INBOUND_IPPACKET_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_INBOUND_IPPACKET_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_INBOUND_IPPACKET_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_INBOUND_IPPACKET_V4_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_IPPACKET_V4_SUB_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_IPPACKET_V4_FLAGS,
   FWPS_FIELD_INBOUND_IPPACKET_V4_INTERFACE_TYPE,
   FWPS_FIELD_INBOUND_IPPACKET_V4_TUNNEL_TYPE,
   FWPS_FIELD_INBOUND_IPPACKET_V4_MAX
} FWPS_FIELDS_INBOUND_IPPACKET_V4;

typedef enum FWPS_FIELDS_INBOUND_IPPACKET_V6_
{
   FWPS_FIELD_INBOUND_IPPACKET_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_INBOUND_IPPACKET_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_INBOUND_IPPACKET_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_INBOUND_IPPACKET_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_INBOUND_IPPACKET_V6_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_IPPACKET_V6_SUB_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_IPPACKET_V6_FLAGS,
   FWPS_FIELD_INBOUND_IPPACKET_V6_INTERFACE_TYPE,
   FWPS_FIELD_INBOUND_IPPACKET_V6_TUNNEL_TYPE,
   FWPS_FIELD_INBOUND_IPPACKET_V6_MAX
} FWPS_FIELDS_INBOUND_IPPACKET_V6;

typedef enum FWPS_FIELDS_OUTBOUND_IPPACKET_V4_
{
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_SUB_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_FLAGS,
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_INTERFACE_TYPE,
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_TUNNEL_TYPE,
   FWPS_FIELD_OUTBOUND_IPPACKET_V4_MAX
} FWPS_FIELDS_OUTBOUND_IPPACKET_V4;

typedef enum FWPS_FIELDS_OUTBOUND_IPPACKET_V6_
{
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_SUB_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_FLAGS,
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_INTERFACE_TYPE,
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_TUNNEL_TYPE,
   FWPS_FIELD_OUTBOUND_IPPACKET_V6_MAX
} FWPS_FIELDS_OUTBOUND_IPPACKET_V6;

typedef enum FWPS_FIELDS_IPFORWARD_V4_
{
   FWPS_FIELD_IPFORWARD_V4_IP_SOURCE_ADDRESS,
   FWPS_FIELD_IPFORWARD_V4_IP_DESTINATION_ADDRESS,
   FWPS_FIELD_IPFORWARD_V4_IP_DESTINATION_ADDRESS_TYPE,
   FWPS_FIELD_IPFORWARD_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_IPFORWARD_V4_IP_FORWARD_INTERFACE,
   FWPS_FIELD_IPFORWARD_V4_SOURCE_INTERFACE_INDEX,
   FWPS_FIELD_IPFORWARD_V4_SOURCE_SUB_INTERFACE_INDEX,
   FWPS_FIELD_IPFORWARD_V4_DESTINATION_INTERFACE_INDEX,
   FWPS_FIELD_IPFORWARD_V4_DESTINATION_SUB_INTERFACE_INDEX,
   FWPS_FIELD_IPFORWARD_V4_FLAGS,
   FWPS_FIELD_IPFORWARD_V4_MAX
} FWPS_FIELDS_IPFORWARD_V4;

typedef enum FWPS_FIELDS_IPFORWARD_V6_
{
   FWPS_FIELD_IPFORWARD_V6_IP_SOURCE_ADDRESS,
   FWPS_FIELD_IPFORWARD_V6_IP_DESTINATION_ADDRESS,
   FWPS_FIELD_IPFORWARD_V6_IP_DESTINATION_ADDRESS_TYPE,
   FWPS_FIELD_IPFORWARD_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_IPFORWARD_V6_IP_FORWARD_INTERFACE,
   FWPS_FIELD_IPFORWARD_V6_SOURCE_INTERFACE_INDEX,
   FWPS_FIELD_IPFORWARD_V6_SOURCE_SUB_INTERFACE_INDEX,
   FWPS_FIELD_IPFORWARD_V6_DESTINATION_INTERFACE_INDEX,
   FWPS_FIELD_IPFORWARD_V6_DESTINATION_SUB_INTERFACE_INDEX,
   FWPS_FIELD_IPFORWARD_V6_FLAGS,
   FWPS_FIELD_IPFORWARD_V6_MAX
} FWPS_FIELDS_IPFORWARD_V6;

typedef enum FWPS_FIELDS_INBOUND_TRANSPORT_V4_
{
   FWPS_FIELD_INBOUND_TRANSPORT_V4_IP_PROTOCOL,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_IP_LOCAL_PORT,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_IP_REMOTE_PORT,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_SUB_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_FLAGS,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_INTERFACE_TYPE,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_TUNNEL_TYPE,
   FWPS_FIELD_INBOUND_TRANSPORT_V4_MAX
} FWPS_FIELDS_INBOUND_TRANSPORT_V4;

#define FWPS_FIELD_INBOUND_TRANSPORT_V4_ICMP_TYPE \
        FWPS_FIELD_INBOUND_TRANSPORT_V4_IP_LOCAL_PORT

#define FWPS_FIELD_INBOUND_TRANSPORT_V4_ICMP_CODE \
        FWPS_FIELD_INBOUND_TRANSPORT_V4_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_INBOUND_TRANSPORT_V6_
{
   FWPS_FIELD_INBOUND_TRANSPORT_V6_IP_PROTOCOL,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_IP_LOCAL_PORT,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_IP_REMOTE_PORT,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_SUB_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_FLAGS,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_INTERFACE_TYPE,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_TUNNEL_TYPE,
   FWPS_FIELD_INBOUND_TRANSPORT_V6_MAX
} FWPS_FIELDS_INBOUND_TRANSPORT_V6;

#define FWPS_FIELD_INBOUND_TRANSPORT_V6_ICMP_TYPE \
        FWPS_FIELD_INBOUND_TRANSPORT_V6_IP_LOCAL_PORT

#define FWPS_FIELD_INBOUND_TRANSPORT_V6_ICMP_CODE \
        FWPS_FIELD_INBOUND_TRANSPORT_V6_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_OUTBOUND_TRANSPORT_V4_
{
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_PROTOCOL,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_LOCAL_PORT,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_REMOTE_PORT,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_SUB_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_DESTINATION_ADDRESS_TYPE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_FLAGS,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_INTERFACE_TYPE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_TUNNEL_TYPE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V4_MAX
} FWPS_FIELDS_OUTBOUND_TRANSPORT_V4;

#define FWPS_FIELD_OUTBOUND_TRANSPORT_V4_ICMP_TYPE \
        FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_LOCAL_PORT

#define FWPS_FIELD_OUTBOUND_TRANSPORT_V4_ICMP_CODE \
        FWPS_FIELD_OUTBOUND_TRANSPORT_V4_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_OUTBOUND_TRANSPORT_V6_
{
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_PROTOCOL,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_LOCAL_PORT,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_REMOTE_PORT,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_SUB_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_DESTINATION_ADDRESS_TYPE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_FLAGS,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_INTERFACE_TYPE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_TUNNEL_TYPE,
   FWPS_FIELD_OUTBOUND_TRANSPORT_V6_MAX
} FWPS_FIELDS_OUTBOUND_TRANSPORT_V6;

#define FWPS_FIELD_OUTBOUND_TRANSPORT_V6_ICMP_TYPE \
        FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_LOCAL_PORT

#define FWPS_FIELD_OUTBOUND_TRANSPORT_V6_ICMP_CODE \
        FWPS_FIELD_OUTBOUND_TRANSPORT_V6_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_STREAM_V4_
{
   FWPS_FIELD_STREAM_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_STREAM_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_STREAM_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_STREAM_V4_IP_LOCAL_PORT,
   FWPS_FIELD_STREAM_V4_IP_REMOTE_PORT,
   FWPS_FIELD_STREAM_V4_DIRECTION,
   FWPS_FIELD_STREAM_V4_MAX
} FWPS_FIELDS_STREAM_V4;

typedef enum FWPS_FIELDS_STREAM_V6_
{
   FWPS_FIELD_STREAM_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_STREAM_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_STREAM_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_STREAM_V6_IP_LOCAL_PORT,
   FWPS_FIELD_STREAM_V6_IP_REMOTE_PORT,
   FWPS_FIELD_STREAM_V6_DIRECTION,
   FWPS_FIELD_STREAM_V6_MAX
} FWPS_FIELDS_STREAM_V6;

typedef enum FWPS_FIELDS_DATAGRAM_DATA_V4_
{
   FWPS_FIELD_DATAGRAM_DATA_V4_IP_PROTOCOL,
   FWPS_FIELD_DATAGRAM_DATA_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_DATAGRAM_DATA_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_DATAGRAM_DATA_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_DATAGRAM_DATA_V4_IP_LOCAL_PORT,
   FWPS_FIELD_DATAGRAM_DATA_V4_IP_REMOTE_PORT,
   FWPS_FIELD_DATAGRAM_DATA_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_DATAGRAM_DATA_V4_INTERFACE_INDEX,
   FWPS_FIELD_DATAGRAM_DATA_V4_SUB_INTERFACE_INDEX,
   FWPS_FIELD_DATAGRAM_DATA_V4_DIRECTION,
   FWPS_FIELD_DATAGRAM_DATA_V4_FLAGS,
   FWPS_FIELD_DATAGRAM_DATA_V4_INTERFACE_TYPE,
   FWPS_FIELD_DATAGRAM_DATA_V4_TUNNEL_TYPE,
   FWPS_FIELD_DATAGRAM_DATA_V4_MAX
} FWPS_FIELDS_DATAGRAM_DATA_V4;

#define FWPS_FIELD_DATAGRAM_DATA_V4_ICMP_TYPE \
        FWPS_FIELD_DATAGRAM_DATA_V4_IP_LOCAL_PORT

#define FWPS_FIELD_DATAGRAM_DATA_V4_ICMP_CODE \
        FWPS_FIELD_DATAGRAM_DATA_V4_IP_REMOTE_PORT


typedef enum FWPS_FIELDS_DATAGRAM_DATA_V6_
{
   FWPS_FIELD_DATAGRAM_DATA_V6_IP_PROTOCOL,
   FWPS_FIELD_DATAGRAM_DATA_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_DATAGRAM_DATA_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_DATAGRAM_DATA_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_DATAGRAM_DATA_V6_IP_LOCAL_PORT,
   FWPS_FIELD_DATAGRAM_DATA_V6_IP_REMOTE_PORT,
   FWPS_FIELD_DATAGRAM_DATA_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_DATAGRAM_DATA_V6_INTERFACE_INDEX,
   FWPS_FIELD_DATAGRAM_DATA_V6_SUB_INTERFACE_INDEX,
   FWPS_FIELD_DATAGRAM_DATA_V6_DIRECTION,
   FWPS_FIELD_DATAGRAM_DATA_V6_FLAGS,
   FWPS_FIELD_DATAGRAM_DATA_V6_INTERFACE_TYPE,
   FWPS_FIELD_DATAGRAM_DATA_V6_TUNNEL_TYPE,
   FWPS_FIELD_DATAGRAM_DATA_V6_MAX
} FWPS_FIELDS_DATAGRAM_DATA_V6;

#define FWPS_FIELD_DATAGRAM_DATA_V6_ICMP_TYPE \
        FWPS_FIELD_DATAGRAM_DATA_V6_IP_LOCAL_PORT

#define FWPS_FIELD_DATAGRAM_DATA_V6_ICMP_CODE \
        FWPS_FIELD_DATAGRAM_DATA_V6_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_INBOUND_ICMP_ERROR_V4_
{
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_EMBEDDED_PROTOCOL,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_EMBEDDED_REMOTE_ADDRESS,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_EMBEDDED_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_EMBEDDED_LOCAL_PORT,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_EMBEDDED_REMOTE_PORT,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_ICMP_TYPE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_ICMP_CODE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_SUB_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_INTERFACE_TYPE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_TUNNEL_TYPE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V4_MAX
} FWPS_FIELDS_INBOUND_ICMP_ERROR_V4;

typedef enum FWPS_FIELDS_INBOUND_ICMP_ERROR_V6_
{
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_EMBEDDED_PROTOCOL,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_EMBEDDED_REMOTE_ADDRESS,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_EMBEDDED_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_EMBEDDED_LOCAL_PORT,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_EMBEDDED_REMOTE_PORT,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_ICMP_TYPE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_ICMP_CODE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_SUB_INTERFACE_INDEX,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_INTERFACE_TYPE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_TUNNEL_TYPE,
   FWPS_FIELD_INBOUND_ICMP_ERROR_V6_MAX
} FWPS_FIELDS_INBOUND_ICMP_ERROR_V6;

typedef enum FWPS_FIELDS_OUTBOUND_ICMP_ERROR_V4_
{
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_ICMP_TYPE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_ICMP_CODE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_SUB_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_INTERFACE_TYPE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_TUNNEL_TYPE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V4_MAX
} FWPS_FIELDS_OUTBOUND_ICMP_ERROR_V4;

typedef enum FWPS_FIELDS_OUTBOUND_ICMP_ERROR_V6_
{
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_IP_LOCAL_PORT,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_IP_REMOTE_PORT,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_SUB_INTERFACE_INDEX,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_INTERFACE_TYPE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_TUNNEL_TYPE,
   FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_MAX
} FWPS_FIELDS_OUTBOUND_ICMP_ERROR_V6;

#define FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_ICMP_TYPE \
        FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_IP_LOCAL_PORT

#define FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_ICMP_CODE \
        FWPS_FIELD_OUTBOUND_ICMP_ERROR_V6_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_ALE_RESOURCE_ASSIGNMENT_V4_
{
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_ALE_APP_ID,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_ALE_USER_ID,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_IP_PROTOCOL,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_ALE_PROMISCUOUS_MODE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_FLAGS,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_INTERFACE_TYPE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_TUNNEL_TYPE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V4_MAX
} FWPS_FIELDS_ALE_RESOURCE_ASSIGNMENT_V4;

typedef enum FWPS_FIELDS_ALE_RESOURCE_ASSIGNMENT_V6_
{
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_ALE_APP_ID,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_ALE_USER_ID,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_IP_PROTOCOL,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_ALE_PROMISCUOUS_MODE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_FLAGS,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_INTERFACE_TYPE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_TUNNEL_TYPE,
   FWPS_FIELD_ALE_RESOURCE_ASSIGNMENT_V6_MAX
} FWPS_FIELDS_ALE_RESOURCE_ASSIGNMENT_V6;

typedef enum FWPS_FIELDS_ALE_AUTH_LISTEN_V4_
{
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_ALE_APP_ID,
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_ALE_USER_ID,
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_FLAGS,
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_INTERFACE_TYPE,
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_TUNNEL_TYPE,
   FWPS_FIELD_ALE_AUTH_LISTEN_V4_MAX
} FWPS_FIELDS_ALE_AUTH_LISTEN_V4;

typedef enum FWPS_FIELDS_ALE_AUTH_LISTEN_V6_
{
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_ALE_APP_ID,
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_ALE_USER_ID,
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_FLAGS,
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_INTERFACE_TYPE,
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_TUNNEL_TYPE,
   FWPS_FIELD_ALE_AUTH_LISTEN_V6_MAX
} FWPS_FIELDS_ALE_AUTH_LISTEN_V6;

typedef enum FWPS_FIELDS_ALE_AUTH_RECV_ACCEPT_V4_
{
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_ALE_APP_ID,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_ALE_USER_ID,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_IP_PROTOCOL,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_IP_REMOTE_PORT,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_ALE_REMOTE_USER_ID,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_ALE_REMOTE_MACHINE_ID,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_FLAGS,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_SIO_FIREWALL_SYSTEM_PORT,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_NAP_CONTEXT,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_INTERFACE_TYPE,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_TUNNEL_TYPE,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_INTERFACE_INDEX,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_SUB_INTERFACE_INDEX,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_MAX
} FWPS_FIELDS_ALE_AUTH_RECV_ACCEPT_V4;

#define FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_ICMP_TYPE \
        FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_IP_LOCAL_PORT

#define FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_ICMP_CODE \
        FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V4_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_ALE_AUTH_RECV_ACCEPT_V6_
{
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_ALE_APP_ID,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_ALE_USER_ID,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_IP_PROTOCOL,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_IP_REMOTE_PORT,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_ALE_REMOTE_USER_ID,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_ALE_REMOTE_MACHINE_ID,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_FLAGS,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_SIO_FIREWALL_SYSTEM_PORT,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_NAP_CONTEXT,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_INTERFACE_TYPE,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_TUNNEL_TYPE,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_INTERFACE_INDEX,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_SUB_INTERFACE_INDEX,
   FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_MAX
} FWPS_FIELDS_ALE_AUTH_RECV_ACCEPT_V6;

#define FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_ICMP_TYPE \
        FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_IP_LOCAL_PORT

#define FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_ICMP_CODE \
        FWPS_FIELD_ALE_AUTH_RECV_ACCEPT_V6_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_ALE_AUTH_CONNECT_V4_
{
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_ALE_APP_ID,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_ALE_USER_ID,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_PROTOCOL,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_REMOTE_PORT,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_ALE_REMOTE_USER_ID,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_ALE_REMOTE_MACHINE_ID,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_DESTINATION_ADDRESS_TYPE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_FLAGS,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_INTERFACE_TYPE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_TUNNEL_TYPE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V4_MAX
} FWPS_FIELDS_ALE_AUTH_CONNECT_V4;

#define FWPS_FIELD_ALE_AUTH_CONNECT_V4_ICMP_TYPE \
        FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_LOCAL_PORT

#define FWPS_FIELD_ALE_AUTH_CONNECT_V4_ICMP_CODE \
        FWPS_FIELD_ALE_AUTH_CONNECT_V4_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_ALE_AUTH_CONNECT_V6_
{
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_ALE_APP_ID,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_ALE_USER_ID,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_PROTOCOL,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_REMOTE_PORT,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_ALE_REMOTE_USER_ID,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_ALE_REMOTE_MACHINE_ID,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_DESTINATION_ADDRESS_TYPE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_FLAGS,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_INTERFACE_TYPE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_TUNNEL_TYPE,
   FWPS_FIELD_ALE_AUTH_CONNECT_V6_MAX
} FWPS_FIELDS_ALE_AUTH_CONNECT_V6;

#define FWPS_FIELD_ALE_AUTH_CONNECT_V6_ICMP_TYPE \
        FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_LOCAL_PORT

#define FWPS_FIELD_ALE_AUTH_CONNECT_V6_ICMP_CODE \
        FWPS_FIELD_ALE_AUTH_CONNECT_V6_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_ALE_FLOW_ESTABLISHED_V4_
{
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_ALE_APP_ID,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_ALE_USER_ID,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_PROTOCOL,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_REMOTE_PORT,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_ALE_REMOTE_USER_ID,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_ALE_REMOTE_MACHINE_ID,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_DESTINATION_ADDRESS_TYPE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_DIRECTION,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_INTERFACE_TYPE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_TUNNEL_TYPE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_MAX
} FWPS_FIELDS_ALE_FLOW_ESTABLISHED_V4;

#define FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_ICMP_TYPE \
        FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_LOCAL_PORT

#define FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_ICMP_CODE \
        FWPS_FIELD_ALE_FLOW_ESTABLISHED_V4_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_ALE_FLOW_ESTABLISHED_V6_
{
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_ALE_APP_ID,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_ALE_USER_ID,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_LOCAL_ADDRESS_TYPE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_LOCAL_PORT,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_PROTOCOL,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_REMOTE_PORT,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_ALE_REMOTE_USER_ID,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_ALE_REMOTE_MACHINE_ID,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_DESTINATION_ADDRESS_TYPE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_LOCAL_INTERFACE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_DIRECTION,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_INTERFACE_TYPE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_TUNNEL_TYPE,
   FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_MAX
} FWPS_FIELDS_ALE_FLOW_ESTABLISHED_V6;

#define FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_ICMP_TYPE \
        FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_LOCAL_PORT

#define FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_ICMP_CODE \
        FWPS_FIELD_ALE_FLOW_ESTABLISHED_V6_IP_REMOTE_PORT

typedef enum FWPS_FIELDS_IPSEC_KM_DEMUX_V4_
{
   FWPS_FIELD_IPSEC_KM_DEMUX_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_IPSEC_KM_DEMUX_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_IPSEC_KM_DEMUX_V4_MAX
} FWPS_FIELDS_IPSEC_KM_DEMUX_V4;

typedef enum FWPS_FIELDS_IPSEC_KM_DEMUX_V6_
{
   FWPS_FIELD_IPSEC_KM_DEMUX_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_IPSEC_KM_DEMUX_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_IPSEC_KM_DEMUX_V6_MAX
} FWPS_FIELDS_IPSEC_KM_DEMUX_V6;

typedef enum FWPS_FIELDS_IPSEC_V4_
{
   FWPS_FIELD_IPSEC_V4_IP_PROTOCOL,
   FWPS_FIELD_IPSEC_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_IPSEC_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_IPSEC_V4_IP_LOCAL_PORT,
   FWPS_FIELD_IPSEC_V4_IP_REMOTE_PORT,
   FWPS_FIELD_IPSEC_V4_MAX
} FWPS_FIELDS_IPSEC_V4;

typedef enum FWPS_FIELDS_IPSEC_V6_
{
   FWPS_FIELD_IPSEC_V6_IP_PROTOCOL,
   FWPS_FIELD_IPSEC_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_IPSEC_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_IPSEC_V6_IP_LOCAL_PORT,
   FWPS_FIELD_IPSEC_V6_IP_REMOTE_PORT,
   FWPS_FIELD_IPSEC_V6_MAX
} FWPS_FIELDS_IPSEC_V6;

typedef enum FWPS_FIELDS_IKEEXT_V4_
{
   FWPS_FIELD_IKEEXT_V4_IP_LOCAL_ADDRESS,
   FWPS_FIELD_IKEEXT_V4_IP_REMOTE_ADDRESS,
   FWPS_FIELD_IKEEXT_V4_MAX
} FWPS_FIELDS_IKEEXT_V4;

typedef enum FWPS_FIELDS_IKEEXT_V6_
{
   FWPS_FIELD_IKEEXT_V6_IP_LOCAL_ADDRESS,
   FWPS_FIELD_IKEEXT_V6_IP_REMOTE_ADDRESS,
   FWPS_FIELD_IKEEXT_V6_MAX
} FWPS_FIELDS_IKEEXT_V6;

typedef enum FWPS_FIELDS_RPC_UM_
{
   FWPS_FIELD_RPC_UM_REMOTE_USER_TOKEN,
   FWPS_FIELD_RPC_UM_IF_UUID,
   FWPS_FIELD_RPC_UM_IF_VERSION,
   FWPS_FIELD_RPC_UM_IF_FLAG,
   FWPS_FIELD_RPC_UM_DCOM_APP_ID,
   FWPS_FIELD_RPC_UM_IMAGE_NAME,
   FWPS_FIELD_RPC_UM_PROTOCOL,
   FWPS_FIELD_RPC_UM_AUTH_TYPE,
   FWPS_FIELD_RPC_UM_AUTH_LEVEL,
   FWPS_FIELD_RPC_UM_SEC_ENCRYPT_ALGORITHM,
   FWPS_FIELD_RPC_UM_SEC_KEY_SIZE,
   FWPS_FIELD_RPC_UM_LOCAL_ADDR_V4,
   FWPS_FIELD_RPC_UM_LOCAL_ADDR_V6,
   FWPS_FIELD_RPC_UM_LOCAL_PORT,
   FWPS_FIELD_RPC_UM_PIPE,
   FWPS_FIELD_RPC_UM_REMOTE_ADDR_V4,
   FWPS_FIELD_RPC_UM_REMOTE_ADDR_V6,
   FWPS_FIELD_RPC_UM_MAX
} FWPS_FIELDS_RPC_UM;

typedef enum FWPS_FIELDS_RPC_EPMAP_
{
   FWPS_FIELD_RPC_EPMAP_REMOTE_USER_TOKEN,
   FWPS_FIELD_RPC_EPMAP_IF_UUID,
   FWPS_FIELD_RPC_EPMAP_IF_VERSION,
   FWPS_FIELD_RPC_EPMAP_PROTOCOL,
   FWPS_FIELD_RPC_EPMAP_AUTH_TYPE,
   FWPS_FIELD_RPC_EPMAP_AUTH_LEVEL,
   FWPS_FIELD_RPC_EPMAP_SEC_ENCRYPT_ALGORITHM,
   FWPS_FIELD_RPC_EPMAP_SEC_KEY_SIZE,
   FWPS_FIELD_RPC_EPMAP_LOCAL_ADDR_V4,
   FWPS_FIELD_RPC_EPMAP_LOCAL_ADDR_V6,
   FWPS_FIELD_RPC_EPMAP_LOCAL_PORT,
   FWPS_FIELD_RPC_EPMAP_PIPE,
   FWPS_FIELD_RPC_EPMAP_REMOTE_ADDR_V4,
   FWPS_FIELD_RPC_EPMAP_REMOTE_ADDR_V6,
   FWPS_FIELD_RPC_EPMAP_MAX
} FWPS_FIELDS_RPC_EPMAP;

typedef enum FWPS_FIELDS_RPC_EP_ADD_
{
   FWPS_FIELD_RPC_EP_ADD_PROCESS_WITH_RPC_IF_UUID,
   FWPS_FIELD_RPC_EP_ADD_PROTOCOL,
   FWPS_FIELD_RPC_EP_ADD_EP_VALUE,
   FWPS_FIELD_RPC_EP_ADD_EP_FLAGS,
   FWPS_FIELD_RPC_EP_ADD_MAX
} FWPS_FIELDS_RPC_EP_ADD;

typedef enum FWPS_FIELDS_RPC_PROXY_CONN_
{
   FWPS_FIELD_RPC_PROXY_CONN_CLIENT_TOKEN,
   FWPS_FIELD_RPC_PROXY_CONN_SERVER_NAME,
   FWPS_FIELD_RPC_PROXY_CONN_SERVER_PORT,
   FWPS_FIELD_RPC_PROXY_CONN_PROXY_AUTH_TYPE,
   FWPS_FIELD_RPC_PROXY_CONN_CLIENT_CERT_KEY_LENGTH,
   FWPS_FIELD_RPC_PROXY_CONN_CLIENT_CERT_OID,
   FWPS_FIELD_RPC_PROXY_CONN_MAX
} FWPS_FIELDS_RPC_PROXY_CONN;

typedef enum FWPS_FIELDS_RPC_PROXY_IF_
{
   FWPS_FIELD_RPC_PROXY_IF_CLIENT_TOKEN,
   FWPS_FIELD_RPC_PROXY_IF_IF_UUID,
   FWPS_FIELD_RPC_PROXY_IF_IF_VERSION,
   FWPS_FIELD_RPC_PROXY_IF_SERVER_NAME,
   FWPS_FIELD_RPC_PROXY_IF_SERVER_PORT,
   FWPS_FIELD_RPC_PROXY_IF_PROXY_AUTH_TYPE,
   FWPS_FIELD_RPC_PROXY_IF_CLIENT_CERT_KEY_LENGTH,
   FWPS_FIELD_RPC_PROXY_IF_CLIENT_CERT_OID,
   FWPS_FIELD_RPC_PROXY_IF_MAX
} FWPS_FIELDS_RPC_PROXY_IF_IF;

#if (NTDDI_VERSION >= NTDDI_LONGHORN)

///////////////////////////////////////////////////////////////////////////////
//
// Network and transport discard reasons.
//
///////////////////////////////////////////////////////////////////////////////

//
// INET_DISCARD_REASON
//
// Define the reasons given by INET modules for discarding incoming datagrams.
//

#ifndef _INET_DISCARD_REASON_DEFINE_
#define _INET_DISCARD_REASON_DEFINE_

typedef enum {
    InetDiscardSourceUnspecified,
    InetDiscardDestinationMulticast,
    InetDiscardHeaderInvalid,
    InetDiscardChecksumInvalid,
    InetDiscardEndpointNotFound
} INET_DISCARD_REASON, *PINET_DISCARD_REASON;

#endif


#ifndef _IP_DISCARD_REASON_DEFINE_
#define _IP_DISCARD_REASON_DEFINE_

typedef enum {
    //
    // Receive path discard reasons.
    //
    IpDiscardBadSourceAddress = 1,
    IpDiscardNotLocallyDestined,
    IpDiscardProtocolUnreachable,
    IpDiscardPortUnreachable,
    IpDiscardBadLength,
    IpDiscardMalformedHeader,
    IpDiscardNoRoute,
    IpDiscardBeyondScope,
    IpDiscardInspectionDrop,
    IpDiscardTooManyDecapsulations,
    IpDiscardAdministrativelyProhibited,

    IpDiscardReceivePathMax = 127,

    //
    // Forward path discard reasons.
    //
    IpDiscardHopLimitExceeded,
    IpDiscardAddressUnreachable,
    IpDiscardForwardPathMax = 255,

    //
    // Internally used discard reasons.
    //
    IpDiscardArbitrationUnhandled,
    IpDiscardMax
} IP_DISCARD_REASON, *PIP_DISCARD_REASON;

#endif




///////////////////////////////////////////////////////////////////////////////
// 
// API for implementing a callout.
//
///////////////////////////////////////////////////////////////////////////////

//////////
// Flags that can specified which entries are present
// in the FWPS_INCOMING_METADATA_VALUES0 structure.
//////////

#define FWPS_METADATA_FIELD_DISCARD_REASON                   0x00000001
#define FWPS_METADATA_FIELD_FLOW_HANDLE                      0x00000002
#define FWPS_METADATA_FIELD_IP_HEADER_SIZE                   0x00000004
#define FWPS_METADATA_FIELD_PROCESS_PATH                     0x00000008
#define FWPS_METADATA_FIELD_TOKEN                            0x00000010
#define FWPS_METADATA_FIELD_PROCESS_ID                       0x00000020
#define FWPS_METADATA_FIELD_SYSTEM_FLAGS                     0x00000040
#define FWPS_METADATA_FIELD_RESERVED                         0x00000080
#define FWPS_METADATA_FIELD_SOURCE_INTERFACE_INDEX           0x00000100
#define FWPS_METADATA_FIELD_DESTINATION_INTERFACE_INDEX      0x00000200
#define FWPS_METADATA_FIELD_TRANSPORT_HEADER_SIZE            0x00000400
#define FWPS_METADATA_FIELD_COMPARTMENT_ID                   0x00000800
#define FWPS_METADATA_FIELD_FRAGMENT_DATA                    0x00001000
#define FWPS_METADATA_FIELD_PATH_MTU                         0x00002000
#define FWPS_METADATA_FIELD_COMPLETION_HANDLE                0x00004000
#define FWPS_METADATA_FIELD_TRANSPORT_ENDPOINT_HANDLE        0x00008000
#define FWPS_METADATA_FIELD_TRANSPORT_CONTROL_DATA           0x00010000
#define FWPS_METADATA_FIELD_REMOTE_SCOPE_ID                  0x00020000
#define FWPS_METADATA_FIELD_PACKET_DIRECTION                 0x00040000

// Provides additional meta-information to the filter engine. This information
// is not processed by the filter engine, but is supplied to the callouts.
// Unlike the FWPS_INCOMING_VALUES0, the schema of the meta-information is not
// fixed. Callouts should not assume that a given FWPS_METADATA_FIELD is
// present or that it is located at a given index in the array.

typedef struct FWPS_INCOMING_METADATA_VALUES0_
{
   // Bitmask representing which values are set.
   UINT32 currentMetadataValues;
   // Internal flags;
   UINT32 flags;
   // Reserved for system use.
   UINT64 reserved;
   // Discard module and reason.
   FWPS_DISCARD_METADATA0 discardMetadata;
   // Flow Handle.
   UINT64 flowHandle;
   // IP Header size.
   UINT32 ipHeaderSize;
   // Transport Header size
   UINT32 transportHeaderSize;
   // Process Path.
   FWP_BYTE_BLOB* processPath;
   // Token used for authorization.
   UINT64 token;
   // Process Id.
   UINT64 processId;
   // Source and Destination interface indices for discard indications.
   UINT32 sourceInterfaceIndex;
   UINT32 destinationInterfaceIndex;
   // Compartment Id for injection APIs.
   ULONG compartmentId;
   // Fragment data for inbound fragments.
   FWPS_INBOUND_FRAGMENT_METADATA0 fragmentMetadata;
   // Path MTU for outbound packets (to enable calculation of fragments).
   ULONG pathMtu;
   // Completion handle (required in order to be able to pend at this layer).
   HANDLE completionHandle;
   // Endpoint handle for use in outbound transport layer injection.
   UINT64 transportEndpointHandle;
   // Remote scope id for use in outbound transport layer injection.
   SCOPE_ID remoteScopeId;
   // Socket control data (and length) for use in outbound transport layer injection.
   WSACMSGHDR* controlData;
   ULONG controlDataLength;
   // Direction for the current packet. Only specified for ALE re-authorization.
   FWP_DIRECTION packetDirection;       
} FWPS_INCOMING_METADATA_VALUES0;

///////////////////////////////////////////////////////////////////////////////
//
// Macro for checking for metadata fields
//
///////////////////////////////////////////////////////////////////////////////

#define FWPS_IS_METADATA_FIELD_PRESENT(metadataValues, metadataField) \
   (((metadataValues)->currentMetadataValues & (metadataField)) == (metadataField))

// Invoked during classification when a callout filter matches.
typedef void (NTAPI *FWPS_CALLOUT_CLASSIFY_FN0)(
                        IN const FWPS_INCOMING_VALUES0* inFixedValues,
                        IN const FWPS_INCOMING_METADATA_VALUES0* inMetaValues,
                        IN OUT void* layerData,
                        IN const FWPS_FILTER0* filter,
                        IN UINT64 flowContext,
                        OUT FWPS_CLASSIFY_OUT0* classifyOut
                        );

// Notifies the callout that a filter invoking it has been added/deleted.
typedef NTSTATUS (NTAPI *FWPS_CALLOUT_NOTIFY_FN0)(
                            IN FWPS_CALLOUT_NOTIFY_TYPE notifyType,
                            IN const GUID* filterKey,
                            IN OUT FWPS_FILTER0* filter
                            );

// Notifies the callout that a flow has been deleted.
typedef void (NTAPI *FWPS_CALLOUT_FLOW_DELETE_NOTIFY_FN0)(
                        IN UINT16 layerId,
                        IN UINT32 calloutId,
                        IN UINT64 flowContext
                        );

// Notify callout that boottime callout has been removed
typedef void (NTAPI *FWPS_CALLOUT_BOOTTIME_CALLOUT_DELETE_NOTIFY_FN0)(
                        IN UINT32 calloutId
                        );
                        
#endif  // NTDDI_VERSION
#ifdef __cplusplus
}
#endif
#endif // FWPSX_H

