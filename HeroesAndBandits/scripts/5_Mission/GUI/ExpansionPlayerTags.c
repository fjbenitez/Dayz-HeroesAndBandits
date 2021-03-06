#ifdef EXPANSIONMOD

modded class IngameHud extends Hud
{
	string 						m_CurrentTaggedPlayer_HABicon = "";
	string 						m_CurrentTaggedPlayer_LastRequested = "";
	protected  ImageWidget		m_PlayerTagHABIcon;
	
	void IngameHud()
	{
		GetRPCManager().AddRPC( "HaB", "RPCReceiveHABIcon", this, SingeplayerExecutionType.Both );
	}

	void RPCReceiveHABIcon( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		if (GetHeroesAndBanditsSettings())
		{ 
			if (GetHeroesAndBanditsSettings().Expansion_EnableIconOnPlayerTag && m_PlayerTag && m_PlayerTagHABIcon)
			{
				Param2< string, string > data;
				if ( !ctx.Read( data ) ) return;
					habPrint("Icon for " + data.param2 + " icon " + data.param1 , "Debug");
			        m_CurrentTaggedPlayer_HABicon = data.param1;
					m_PlayerTagHABIcon.LoadImageFile( 0, m_CurrentTaggedPlayer_HABicon, true );	
			}
		}
	}
	
	//============================================
	// Override ShowPlayerTag
	//============================================
	override void ShowPlayerTag( float timeslice )
	{	
		if (GetHeroesAndBanditsSettings())
		{ 
			if (GetHeroesAndBanditsSettings().Expansion_EnableIconOnPlayerTag)
			{
				if ( m_PlayerTag && m_CurrentTaggedPlayer && m_CurrentTaggedPlayer.GetIdentity() )
				{ 
					if ( m_CurrentTaggedPlayer.GetIdentityName() != m_CurrentTaggedPlayer_LastRequested){ //perventing icon from being grabbed too manytimes
						GetRPCManager().SendRPC("HaB", "RPCRequestHABIcon", new Param1< string >( m_CurrentTaggedPlayer.GetIdentityName() ), true);
						m_CurrentTaggedPlayer_LastRequested = m_CurrentTaggedPlayer.GetIdentityName();
					}
				}
			}
		}
		super.ShowPlayerTag( timeslice );
		if (m_PlayerTag && !m_PlayerTagHABIcon){
			m_PlayerTagHABIcon = ImageWidget.Cast( m_PlayerTag.FindAnyWidget( "TagIcon" ) );
		}
		if (GetHeroesAndBanditsSettings() && m_PlayerTagText){
			if (GetHeroesAndBanditsSettings().Expansion_HideNameOnPlayerTag){
				m_PlayerTagText.SetText( "" );
			}
		}
		if (m_CurrentTaggedPlayer == null && m_PlayerTagHABIcon){
			m_CurrentTaggedPlayer_LastRequested = "";
			m_PlayerTagHABIcon.SetAlpha( 0 );
			m_PlayerTagHABIcon.Show( false );
		} else if (m_CurrentTaggedPlayer && m_PlayerTagHABIcon ) {
			m_PlayerTagHABIcon.SetAlpha( 1 );
			m_PlayerTagHABIcon.Show( true );
		}
	}
}
#endif