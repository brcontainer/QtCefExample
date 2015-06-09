#include "stdafx.h"
#include "QCefClientHandler.h"
#include "qcefmessageevent.h"

namespace
{
	QCefClientHandler * g_instance = nullptr;
}

QCefClientHandler::QCefClientHandler()
{
}


QCefClientHandler::~QCefClientHandler()
{
}

QCefClientHandler* QCefClientHandler::GetInstance()
{
	return g_instance;
}