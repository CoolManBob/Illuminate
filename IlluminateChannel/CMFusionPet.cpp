#include "CMChangeLooting.h"

bool CMChangeLooting::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;
    
    std::string setNewPetName;
    setNewPetName.reserve(62);
    Int8 keepParentPetSkills, keepParentPetAppearance;
    Int64 firstPet, secondPet;

    *inPacket >> setNewPetName; // Name our new pet being born
    *inPacket >> firstPet; //Who is our parent pet
    *inPacket >> secondPet; //Who is the pet we are breeding with our parent pet
    *inPacket >> keepParentPetSkills; //Did we select to keep our parent pet's skills?
    *inPacket >> keepParentPetAppearance; //Did we select to keep our parent pet's appearance

    /* Implement Logic here */

    /*
    public void runImpl() {
        Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            ServantController servantController = player.getServantController();
            Servant pet1 = servantController.getServant(this.pet1ObjectId);
            Servant pet2 = servantController.getServant(this.pet2ObjectId);
            if (pet1 == null || pet2 == null) {
                return;
            }
            if (pet1.getServantType() != EServantType.Pet || pet2.getServantType() != EServantType.Pet) {
                return;
            }
            if (pet1.getServantState() != EServantState.Stable || pet2.getServantState() != EServantState.Stable) {
                return;
            }
            if (Math.abs(pet1.getPetTemplate().getTier() - pet2.getPetTemplate().getTier()) > 1) {
                return;
            }
            servantController.delete(pet1);
            servantController.delete(pet2);
            PetTemplate pet1template = pet1.getPetTemplate();
            PetTemplate pet2template = pet2.getPetTemplate();
            int resultTier = PetFusionData.getInstance().getResultTierFor(pet1template.getRace(), pet1template.getKind(), Math.min(pet1template.getTier(), pet2template.getTier()));
            List petTemplates = PetData.getInstance().getTemplates().stream().filter(template -> template.getTier() == resultTier && template.getRace() == pet1template.getRace() && template.getKind() == pet1template.getKind()).collect(Collectors.toList());
            if (!petTemplates.isEmpty()) {
                int actionIndex = 0;
                PetTemplate resultPetTemplate = (PetTemplate) petTemplates.get(Rnd.get((int) petTemplates.size()));
                switch (this.petFormOption) {
                    case 0: {
                        actionIndex = PetChangeLookTable.getInstance().getRandomActionIndex(resultPetTemplate.getPetChangeLookKey());
                        break;
                    }
                    case 1: {
                        actionIndex = pet2.getActionIndex();
                        break;
                    }
                    case 2: {
                        actionIndex = pet1.getActionIndex();
                    }
                }
                BitMask resultEquipSkillBitMask = new BitMask(38);
                switch (this.petSkillOption) {
                    case 0: {
                        for (int index = 0; index < resultTier; ++index) {
                            int skillIndex = PetEquipSkillAquireData.getInstance().getRandomSkillIndex(resultPetTemplate.getEquipSkillAquireKey(), null);
                            if (skillIndex <= 0) continue;
                            resultEquipSkillBitMask.setBit(skillIndex);
                        }
                        break;
                    }
                    case 1: {
                        resultEquipSkillBitMask = pet2.getEquipSkillsBitMask();
                        int skillIndex = PetEquipSkillAquireData.getInstance().getRandomSkillIndex(resultPetTemplate.getEquipSkillAquireKey(), resultEquipSkillBitMask);
                        if (skillIndex <= 0) break;
                        resultEquipSkillBitMask.setBit(skillIndex);
                        break;
                    }
                    case 2: {
                        resultEquipSkillBitMask = pet1.getEquipSkillsBitMask();
                        int skillIndex = PetEquipSkillAquireData.getInstance().getRandomSkillIndex(resultPetTemplate.getEquipSkillAquireKey(), resultEquipSkillBitMask);
                        if (skillIndex <= 0) break;
                        resultEquipSkillBitMask.setBit(skillIndex);
                    }
                }
                if (resultPetTemplate != null) {
                    Servant servant = new Servant(resultPetTemplate, player, this.newPetName);
                    servant.setFormIndex(actionIndex);
                    servantController.add(servant);
                    servant.getEquipSkillsBitMask().setMask(resultEquipSkillBitMask.getMask());
                    servant.applyEquipSkills();
                    player.sendPacket(new SMDeactivePetInfo(Collections.singletonList(servant), EPacketTaskType.FusionPet));
                }
            } else {
                log.warn("Not found PetTemplate for upgrading pets: {} and {}", (Object) pet1.getCreatureId(), (Object) pet2.getCreatureId());
            }
        }
    }*/

    return true;
}