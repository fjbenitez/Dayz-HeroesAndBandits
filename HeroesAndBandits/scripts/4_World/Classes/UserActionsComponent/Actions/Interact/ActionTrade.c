#ifdef HABTRADERADDON
modded class ActionTrade: ActionInteractBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
        PlayerBase sourcePlayer = PlayerBase.Cast(player);
		if (sourcePlayer.habTraderIsBlocked()){
			habPrint("BLOCKING TRADE!!!!!!!!!","Debug")
			
			return false;
		}
		
        return super.ActionCondition( player, target, item );
	}
}
#endif