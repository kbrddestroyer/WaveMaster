// Fill out your copyright notice in the Description page of Project Settings.


#include "WMBaseInteractable.h"
#include "AMainCharacterBase.h"

// Sets default values
AWMBaseInteractable::AWMBaseInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);

	// Setup delegate callbacks
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AWMBaseInteractable::OnSphereOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AWMBaseInteractable::OnSphereOverlapEnd);
}

// Called when the game starts or when spawned
void AWMBaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWMBaseInteractable::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAMainCharacterBase* PlayerCharacter = Cast<AAMainCharacterBase>(OtherActor);
	if (PlayerCharacter == nullptr) {return;}

	PlayerCharacter->AddInteractableInSight(this);
	StartInteractionSignalization();
}

void AWMBaseInteractable::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAMainCharacterBase* PlayerCharacter = Cast<AAMainCharacterBase>(OtherActor);
	if (PlayerCharacter == nullptr) {return;}

	PlayerCharacter->RemoveInteractableInSight(this);
	StopInteractionSignalization();
}

// Called every frame
void AWMBaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

