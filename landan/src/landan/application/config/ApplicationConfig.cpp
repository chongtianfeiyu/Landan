//////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include "ApplicationConfig.h"

//////////////////////////////////////////////////////////////////////
// NAMESPACE /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

namespace landan {

	//////////////////////////////////////////////////////////////////////
	// STATICS ///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS //////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	ApplicationConfig::ApplicationConfig()
	:m_applicationType(application::BASIC), m_updateType(application::RUN_ONCE), m_renderType(application::NONE), m_frameRate(60.0f)
	{

	}

	//////////////////////////////////////////////////////////////////////
	// DESTRUCTOR ////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	ApplicationConfig::~ApplicationConfig() 
	{

	}

	//////////////////////////////////////////////////////////////////////
	// GETTERS/SETTERS ///////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	application::APPLICATION_TYPE ApplicationConfig::GetApplicationType()
	{
		return m_applicationType;
	}

	void ApplicationConfig::SetApplicationType(application::APPLICATION_TYPE applicationType)
	{
		m_applicationType = applicationType;
	}

	application::UPDATE_TYPE ApplicationConfig::GetUpdateType()
	{
		return m_updateType;
	}

	void ApplicationConfig::SetUpdateType(application::UPDATE_TYPE updateType)
	{
		m_updateType = updateType;
	}

	application::RENDER_TYPE ApplicationConfig::GetRenderType()
	{
		return m_renderType;
	}

	void ApplicationConfig::SetRenderType(application::RENDER_TYPE renderType)
	{
		m_renderType = renderType;
	}

	f32 ApplicationConfig::GetFrameRate()
	{
		return m_frameRate;
	}

	void ApplicationConfig::SetFrameRate(f32 frameRate)
	{
		m_frameRate = frameRate;
	}



}